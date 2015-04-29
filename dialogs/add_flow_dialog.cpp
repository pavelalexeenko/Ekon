#include "add_flow_dialog.h"
#include "dialogs/add_group_to_flow_dialog.h"

AddFlowDialog::AddFlowDialog(QWidget *parent):
    QDialog(parent)
  , nameLineEdit(new QLineEdit(this))
  , groupsListWidget(new QListWidget(this))
  , notePlainTextEdit(new QPlainTextEdit(this))
  , addGroupButton(new QPushButton(QString("&Добавить группу"), this))
  , removeGroupButton(new QPushButton(QString("&Удалить группу"), this))
  , addButton(new QPushButton(QString("&Добавить"), this))
{
    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(addGroupButton, SIGNAL(clicked()), this, SLOT(addGroups()));

    QFormLayout *formLayout = new QFormLayout(this);

    QFormLayout *buttonsLayout = new QFormLayout(this);
    buttonsLayout->addRow(addGroupButton, removeGroupButton);

    formLayout->addRow(tr("&Название потока:"), nameLineEdit);
    formLayout->addRow(tr("Список групп"), groupsListWidget);
    formLayout->addRow(tr(""), buttonsLayout);
    formLayout->addRow(tr("&Примечание:"), notePlainTextEdit);
    formLayout->addRow(tr(""), addButton);
    setLayout(formLayout);
}

void AddFlowDialog::addRow()
{
    qDebug() << __FUNCTION__;

    if (nameLineEdit->text().isEmpty() ||
            groupsListWidget->count() == 0)
    {
        QMessageBox::critical(this, tr("Error"), tr("Some fields are empty."), QMessageBox::Ok);
        return;
    }

    Flow flow;
    flow.setName(nameLineEdit->text());
    flow.setNote(notePlainTextEdit->toPlainText());

    QSet<int> ids;
    for(int i = 0; i < groupsListWidget->count(); ++i)
    {
        QListWidgetItem* item = groupsListWidget->item(i);
        ids.insert(item->data(Qt::UserRole).getId());
    }

    flow.setGroupIds(ids);

    if (DbService::getInstance()->addFlow(flow))
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Database error while adding a flow."), QMessageBox::Ok);
}

void AddFlowDialog::addGroups()
{
    qDebug() << __FUNCTION__;
    AddGroupToFlowDialog *agtfd = new AddGroupToFlowDialog(this);
    connect(agtfd, SIGNAL(accepted()), this, SLOT(refresh()));
    agtfd->exec();
}
