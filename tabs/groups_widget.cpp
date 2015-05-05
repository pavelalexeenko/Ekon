#include "groups_widget.h"
#include "dialogs/add_group_dialog.h"
#include "tables/worker_widget.h"

GroupsWidget::GroupsWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << __FUNCTION__;

    QStringList columnNames;
    columnNames << "ID"
                << "Название"
                << "Количество студентов"
                << "Курс"
                << "Количество подгрупп"
                << "Семестр"
                << "Факультет"
                << "Специальность"
                << "Примечание";

    groupsTableModel = EkonTables::createTableModel(this, "DRT_GROUPS", columnNames);
    groupsTableView = EkonTables::createTableView(this, groupsTableModel);

    controlWidget = new ControlWidget(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(groupsTableView);
    layout->addWidget(controlWidget);

    this->setLayout(layout);

    connect(controlWidget, SIGNAL(addRow()), this, SLOT(addRow()));
    connect(controlWidget, SIGNAL(removeRow()), this, SLOT(deleteRow()));
}

void GroupsWidget::addRow()
{
    qDebug() << __FUNCTION__;
    AddGroupDialog *agd = new AddGroupDialog(this);
    connect(agd, SIGNAL(accepted()), this, SLOT(refresh()));
    agd->exec();
}

void GroupsWidget::refresh()
{
    qDebug() << __FUNCTION__;
    groupsTableModel->select();
}

void GroupsWidget::deleteRow()
{
    qDebug() << __FUNCTION__;

    if (DbService::getInstance()->deleteGroup(groupsTableModel->data(groupsTableModel->index(groupsTableView->currentIndex().row(), 0)).toInt()))
        this->refresh();
}
