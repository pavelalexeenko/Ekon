#include "flows_widget.h"
#include "dialogs/add_flow_dialog.h"

FlowsWidget::FlowsWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << __FUNCTION__;

    QStringList columnNames;
    columnNames << "ID"
                << "Название потока"
                << "Список групп";

    flowsTableModel = EkonTables::createTableModel(this, "VIEW_FLOWS", columnNames);
    flowsTableView = EkonTables::createTableView(this, flowsTableModel);
    flowsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    controlWidget = new ControlWidget(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(flowsTableView);
    layout->addWidget(controlWidget);

    this->setLayout(layout);

    connect(controlWidget, SIGNAL(addRow()), this, SLOT(addRow()));
}

void FlowsWidget::addRow()
{
    qDebug() << __FUNCTION__;
    AddFlowDialog *afd = new AddFlowDialog(this);
    connect(afd, SIGNAL(accepted()), this, SLOT(refresh()));
    afd->exec();
}

void FlowsWidget::refresh()
{
    qDebug() << __FUNCTION__;
    flowsTableModel->select();
}
