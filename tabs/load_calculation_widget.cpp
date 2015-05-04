#include "load_calculation_widget.h"
#include "dialogs/add_loadcalculation_dialog.h"

LoadCalculationWidget::LoadCalculationWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << __FUNCTION__;

    QStringList columnNames;
    columnNames << "ID"
                << "Название дисциплины"
                << "Название потока"
                << "Лекции"
                << "Лабоработные"
                << "Практики"
                << "Консультации"
                << "Зачет"
                << "TESTS"
                << "Текущие консультации"
                << "INTRODUCTORY PRACTICE"
                << "Преддипломная практика"
                << "Курсовая работа"
                << "GUIDED_INDEPENDENT_WORK"
                << "Контрольная работа"
                << "GRADUATION_DESIGN "
                << "GUIDE_GRADUATE"
                << "Экзамен"
                << "ГЭК"
                << "GUIDE_CHAIR"
                << "УИРС";

    loadCalculationTableModel = EkonTables::createTableModel(this, "VIEW_LOAD_CALCULATION", columnNames);
    loadCalculationTableView = EkonTables::createTableView(this, loadCalculationTableModel);

    loadCalculationTableView->setStyleSheet("QHeaderView::section {background-color:grey}");
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

    AddLoadcalculationDialog *ald = new AddLoadcalculationDialog(this);
    connect(ald, SIGNAL(accepted()), this, SLOT(refresh()));
    ald->exec();
}

void LoadCalculationWidget::refresh()
{
    qDebug() << __FUNCTION__;
    loadCalculationTableModel->select();
}
