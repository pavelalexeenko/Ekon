#include "load_calculation_widget.h"

LoadCalculationWidget::LoadCalculationWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << __FUNCTION__;

    QStringList columnNames;
    columnNames << "ID"
                << "Название дисциплины"
                << "Название потока";

    QList<QPair<int, QSqlRelation> > relations;
    relations.append(qMakePair(1, QSqlRelation("DRT_DISCIPLINES", "DSC_ID", "DSC_NAME")));
    relations.append(qMakePair(2, QSqlRelation("DRT_FLOWS", "FLW_ID", "FLW_NAME")));

    loadCalculationTableModel = EkonTables::createRelationalTableModel(this, "DRT_LOAD_CALCULATION", columnNames, relations);
    loadCalculationTableView = EkonTables::createRelationTableView(this, loadCalculationTableModel);

    controlWidget = new ControlWidget(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(loadCalculationTableView);
    layout->addWidget(controlWidget);

    this->setLayout(layout);

    connect(controlWidget, SIGNAL(addRow()), this, SLOT(addRow()));
}

void LoadCalculationWidget::addRow()
{
    qDebug() << __FUNCTION__;
}

void LoadCalculationWidget::refresh()
{
    qDebug() << __FUNCTION__;
    loadCalculationTableModel->select();
}
