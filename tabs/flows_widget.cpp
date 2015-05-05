#include "flows_widget.h"
#include "dialogs/add_flow_dialog.h"

FlowsWidget::FlowsWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << __FUNCTION__;

    QStringList columnNames;
    columnNames << "ID"
                << "Название потока"
                << "Список групп"
                << "Примечание";

    flowsTableModel = EkonTables::createTableModel(this, "VIEW_FLOWS", columnNames);
    flowsTableView = EkonTables::createTableView(this, flowsTableModel);
    flowsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    controlWidget = new ControlWidget(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(flowsTableView);
    layout->addWidget(controlWidget);

    this->setLayout(layout);

    connect(controlWidget, SIGNAL(addRow()), this, SLOT(addRow()));
    connect(controlWidget, SIGNAL(removeRow()), this, SLOT(deleteRow()));
    connect(flowsTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editRow(QModelIndex)));
}

void FlowsWidget::addRow()
{
    qDebug() << __FUNCTION__;
    AddFlowDialog *afd = new AddFlowDialog(this);
    connect(afd, SIGNAL(accepted()), this, SLOT(refresh()));
    afd->exec();
}

void FlowsWidget::deleteRow()
{
    qDebug() << __FUNCTION__;

    if (DbService::getInstance()->deleteFlow(flowsTableModel->data(flowsTableModel->index(flowsTableView->currentIndex().row(), 0)).toInt()))
        this->refresh();
}

void FlowsWidget::refresh()
{
    qDebug() << __FUNCTION__;
    flowsTableModel->select();
}

void FlowsWidget::editRow(const QModelIndex &index)
{
    qDebug() << __FUNCTION__;
    AddFlowDialog *afd = new AddFlowDialog(flowsTableModel->data(flowsTableModel->index(index.row(), 0)).toInt(), this);
    connect(afd, SIGNAL(accepted()), this, SLOT(refresh()));
    afd->exec();
}
