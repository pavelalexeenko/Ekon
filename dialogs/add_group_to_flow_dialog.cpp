#include "add_group_to_flow_dialog.h"

AddGroupToFlowDialog::AddGroupToFlowDialog(QWidget *parent) :
    QDialog(parent)
  , groupsListWidget(new QListWidget())
  , addButton(new QPushButton())
  , exitButton(new QPushButton())
{
    QList<Group> groups = DbService::getInstance()->getAllGroups();

    for (auto group : groups)
    {
        QListWidgetItem* item = new QListWidgetItem(groupsListWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        item->setCheckState(Qt::Unchecked); // AND initialize check state
        item->setText(group.getName());
        item->setData(Qt::UserRole, QVariant(group));
        groupsListWidget->addItem(item);
    }

    connect(addButton, SIGNAL(clicked()), this, SLOT(accept()));

    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow(QLabel(QString("Список групп:")).setAlignment(Qt::AlignLeft));
    formLayout->addRow(groupsListWidget);
    formLayout->addRow(exitButton, addButton);
    setLayout(formLayout);
}
