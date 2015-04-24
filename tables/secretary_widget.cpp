#include "secretary_widget.h"

SecretaryWidget::SecretaryWidget(QWidget *parent) :
    EkonTabWidget(parent)
{
    addLoadCalculationTab();
    addLoadDistributionTab();
}

void SecretaryWidget::search(QString str)
{
    qDebug() << "SecretaryWidget::search(QString \"" + str + "\")";
}

void SecretaryWidget::refresh()
{
    qDebug() << "SecretaryWidget::refresh()";
    loadCalculationTableModel->select();
    loadDistributionTableModel->select();
}

void SecretaryWidget::addRow()
{
    qDebug() << "SecretaryWidget::addRow()";
}

void SecretaryWidget::addLoadCalculationTab()
{
    QStringList columnNames;
    columnNames << "ID"
                << "Название дисциплины"
                << "Название потока";

    QList<QPair<int, QSqlRelation> > relations;
    relations.append(qMakePair(1, QSqlRelation("DRT_DISCIPLINES", "DSC_ID", "DSC_NAME")));
    relations.append(qMakePair(2, QSqlRelation("DRT_FLOWS", "FLW_ID", "FLW_NAME")));

    QWidget *widget = new QWidget();
    loadCalculationTableModel = createRelationalTableModel(widget, "DRT_LOAD_CALCULATION", columnNames, relations);
    loadCalculationTableView = createRelationTableView(widget, loadCalculationTableModel);

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(loadCalculationTableView);

    this->addTab(widget, QString("Распределение дисциплин"));
}

void SecretaryWidget::addLoadDistributionTab()
{
    QStringList columnNames;
    columnNames << "ID"
                << "ФИО преподавателя"
                << "Название дисциплины";

    QList<QPair<int, QSqlRelation> > relations;
    relations.append(qMakePair(1, QSqlRelation("DRT_TEACHERS", "TCH_ID", "TCH_NAME")));
    relations.append(qMakePair(2, QSqlRelation("VIEW_LOAD_CALCULATION", "LCLV_ID", "LCLV_NAME")));

    QWidget *widget = new QWidget();
    loadDistributionTableModel = createRelationalTableModel(widget, "DRT_LOAD_DISTRIBUTION", columnNames, relations);
    loadDistributionTableView = createRelationTableView(widget, loadDistributionTableModel);

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(loadDistributionTableView);

    this->addTab(widget, QString("Распределение нагрузки"));
}

