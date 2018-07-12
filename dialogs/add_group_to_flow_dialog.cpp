#include "add_group_to_flow_dialog.h"

AddGroupToFlowDialog::AddGroupToFlowDialog(QWidget *parent) :
    QDialog(parent)
  , groupsListWidget(new QListWidget())
  , addButton(new QPushButton(QString("&Добавить")))
  , exitButton(new QPushButton(QString("&Отмена")))
{
    qDebug() << __FUNCTION__;
    setWindowTitle("Выбор групп");

    groupsListWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QList<Group> groups = DbService::getInstance()->getAllGroups();

    for (auto group : groups)
    {
        QListWidgetItem* item = new QListWidgetItem(groupsListWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        item->setText(group.getName());
        item->setData(Qt::UserRole, group.getId());
        groupsListWidget->addItem(item);
    }

    connect(addButton, SIGNAL(clicked()), this, SLOT(setSelectedIds()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));

    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow(new QLabel(QString("Список групп:")));
    formLayout->addRow(groupsListWidget);
    formLayout->addRow(exitButton, addButton);
    setLayout(formLayout);
}

QList<int> AddGroupToFlowDialog::getSelectedGroupsId() const
{
    qDebug() << __FUNCTION__;
    return selectedIds;
}

void AddGroupToFlowDialog::setSelectedIds()
{
    qDebug() << __FUNCTION__;

    selectedIds.clear();

    for(int i = 0; i < groupsListWidget->count(); ++i)
    {
        QListWidgetItem* item = groupsListWidget->item(i);
        if (item->checkState() == Qt::Checked)
            selectedIds.append(item->data(Qt::UserRole).toInt());
    }

    this->accept();
}
