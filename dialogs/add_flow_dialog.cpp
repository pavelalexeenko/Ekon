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
  , _id(-1)
{
    qDebug() << __FUNCTION__;
    setWindowTitle("Добавление потока");

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(addGroupButton, SIGNAL(clicked()), this, SLOT(addGroups()));
    connect(removeGroupButton, SIGNAL(clicked()), this, SLOT(removeGroups()));

    QFormLayout *formLayout = new QFormLayout(this);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(addGroupButton);
    buttonsLayout->addWidget(removeGroupButton);

    formLayout->addRow(tr("&Название потока:"), nameLineEdit);
    formLayout->addRow(tr("Список групп"), groupsListWidget);
    formLayout->addRow(tr(""), buttonsLayout);
    formLayout->addRow(tr("&Примечание:"), notePlainTextEdit);
    formLayout->addRow(tr(""), addButton);
    setLayout(formLayout);
}

AddFlowDialog::AddFlowDialog(const int& id, QWidget *parent):
    QDialog(parent)
  , nameLineEdit(new QLineEdit(this))
  , groupsListWidget(new QListWidget(this))
  , notePlainTextEdit(new QPlainTextEdit(this))
  , addGroupButton(new QPushButton(QString("&Добавить группу"), this))
  , removeGroupButton(new QPushButton(QString("&Удалить группу"), this))
  , addButton(new QPushButton(QString("&Сохранить"), this))
  , _id(id)
{
    qDebug() << __FUNCTION__;

    setWindowTitle("Изменение потока");

    connect(addButton, SIGNAL(clicked()), this, SLOT(changeFlow()));
    connect(addGroupButton, SIGNAL(clicked()), this, SLOT(addGroups()));
    connect(removeGroupButton, SIGNAL(clicked()), this, SLOT(removeGroups()));

    QFormLayout *formLayout = new QFormLayout(this);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(addGroupButton);
    buttonsLayout->addWidget(removeGroupButton);

    formLayout->addRow(tr("&Название потока:"), nameLineEdit);
    formLayout->addRow(tr("Список групп"), groupsListWidget);
    formLayout->addRow(tr(""), buttonsLayout);
    formLayout->addRow(tr("&Примечание:"), notePlainTextEdit);
    formLayout->addRow(tr(""), addButton);
    setLayout(formLayout);

    Flow flow = DbService::getInstance()->getFlowById(_id);
    nameLineEdit->setText(flow.getName());
    for (auto id : flow.getGroupIds())
    {
        QListWidgetItem* item = new QListWidgetItem(groupsListWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        item->setData(Qt::UserRole, id);
        item->setText(DbService::getInstance()->getGroupNameById(id));
        groupsListWidget->addItem(item);
    }
    notePlainTextEdit->setPlainText(flow.getNote());
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
        ids.insert(item->data(Qt::UserRole).toInt());
    }

    flow.setGroupIds(ids);

    if (DbService::getInstance()->addFlow(flow))
        this->accept();
    else
        QMessageBox::critical(this, tr("Ошибка!"), tr("Поток с таким названием уже существует."), QMessageBox::Ok);
}

void AddFlowDialog::addGroups()
{
    qDebug() << __FUNCTION__;
    AddGroupToFlowDialog *agtfd = new AddGroupToFlowDialog(this);
    agtfd->exec();

    QList<int> ids = agtfd->getSelectedGroupsId();

    QSet<int> currentIds;
    for(int i = 0; i < groupsListWidget->count(); ++i)
    {
        QListWidgetItem* item = groupsListWidget->item(i);
        currentIds.insert(item->data(Qt::UserRole).toInt());
    }

    for (auto id : ids)
    {
        if (!currentIds.contains(id))
        {
            QListWidgetItem* item = new QListWidgetItem(groupsListWidget);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
            item->setData(Qt::UserRole, id);
            item->setText(DbService::getInstance()->getGroupNameById(id));
            groupsListWidget->addItem(item);
        }
    }

    groupsListWidget->sortItems(Qt::AscendingOrder);
}

void AddFlowDialog::removeGroups()
{
    qDebug() << __FUNCTION__;
    QList<QListWidgetItem*> list;
    for(int i = 0; i < groupsListWidget->count(); ++i)
    {
        QListWidgetItem* item = groupsListWidget->item(i);
        if (item->checkState() == Qt::Checked)
            list.append(item);
    }

    for (auto &item : list)
    {
        delete item;
    }

    groupsListWidget->sortItems(Qt::AscendingOrder);
}

void AddFlowDialog::changeFlow()
{
    qDebug() << __FUNCTION__;

    if (nameLineEdit->text().isEmpty() ||
            groupsListWidget->count() == 0)
    {
        QMessageBox::critical(this, tr("Error"), tr("Some fields are empty."), QMessageBox::Ok);
        return;
    }

    Flow flow;
    flow.setId(_id);
    flow.setName(nameLineEdit->text());
    flow.setNote(notePlainTextEdit->toPlainText());

    QSet<int> ids;
    for(int i = 0; i < groupsListWidget->count(); ++i)
    {
        QListWidgetItem* item = groupsListWidget->item(i);
        ids.insert(item->data(Qt::UserRole).toInt());
    }

    flow.setGroupIds(ids);

    if (DbService::getInstance()->updateFlow(flow))
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Database error while adding a flow."), QMessageBox::Ok);
}

