#include "load_distribution_widget.h"

LoadDistributionWidget::LoadDistributionWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << __FUNCTION__;

    QStringList columnNames;
    columnNames << "ID"
                << "ФИО преподавателя"
                << "Название дисциплины";

    QList<QPair<int, QSqlRelation> > relations;
    relations.append(qMakePair(1, QSqlRelation("DRT_TEACHERS", "TCH_ID", "TCH_NAME")));
    relations.append(qMakePair(2, QSqlRelation("VIEW_LOAD_CALCULATION", "LCLV_ID", "LCLV_NAME")));

    loadDistributionTableModel = EkonTables::createRelationalTableModel(this, "DRT_LOAD_DISTRIBUTION", columnNames, relations);
    loadDistributionTableView = EkonTables::createRelationTableView(this, loadDistributionTableModel);

    controlWidget = new ControlWidget(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(loadDistributionTableView);
    layout->addWidget(controlWidget);

    this->setLayout(layout);

    connect(controlWidget, SIGNAL(addRow()), this, SLOT(addRow()));
}

void LoadDistributionWidget::addRow()
{
    qDebug() << __FUNCTION__;
}

void LoadDistributionWidget::refresh()
{
    qDebug() << __FUNCTION__;
    loadDistributionTableModel->select();
}
