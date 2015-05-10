#include "load_calculation_widget.h"
#include "dialogs/add_loadcalculation_dialog.h"
#include "implementations/read_only_delegate.h"

LoadCalculationWidget::LoadCalculationWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << __FUNCTION__;

    QStringList columnNames;
    columnNames << "ID"
                << "DSC_ID"
                << "Название\n дисциплины"
                << "FLW_ID"
                << "Название\n потока"
                << "Лекции"
                << "Лабоработные"
                << "Практики"
                << "Консультации"
                << "Экзамен"
                << "Зачет"
                << "Текущая\n консультации"
                << "Ознакомительная\n практика"
                << "Преддипломная\n практика"
                << "Курсовая\n работа"
                << "Управляемая\n самост. работа"
                << "Контрольная\n работа"
                << "Дипломное\n проектирование"
                << "Рук-во\n аспирантами"
                << "Гос экзамен"
                << "ГЭК"
                << "Руководство\n кафедрой"
                << "УИРС";

    loadCalculationTableModel = EkonTables::createTableModel(this, "VIEW_LOAD_CALCULATION", columnNames);

    filterProxyModel = new CheckableSortFilterProxyModel(this);
    QList<int> readonlyCols;
    for (int i = 0; i < 23; i++)
        readonlyCols.append(i);

    filterProxyModel->setParameters(QList<int>(), readonlyCols, QList<int>());
    filterProxyModel->setSourceModel(loadCalculationTableModel);

    loadCalculationTableView = EkonTables::createTableView(this, filterProxyModel);
    loadCalculationTableView->hideColumn(1);
    loadCalculationTableView->hideColumn(3);

    //loadCalculationTableView->setStyleSheet("QTableView::item {background-color: #D4D0C8; color: black;}");
    controlWidget = new ControlWidget(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(loadCalculationTableView);
    layout->addWidget(controlWidget);

    this->setLayout(layout);

    connect(controlWidget, SIGNAL(addRow()), this, SLOT(addRow()));
    connect(controlWidget, SIGNAL(removeRow()), this, SLOT(deleteRow()));
    connect(controlWidget, SIGNAL(filter(QString)), filterProxyModel, SLOT(setFilterFixedString(QString)));
    connect(controlWidget, SIGNAL(search(QString)), filterProxyModel, SLOT(setColorFilterString(QString)));
}

void LoadCalculationWidget::addRow()
{
    qDebug() << __FUNCTION__;

    AddLoadcalculationDialog *alcd = new AddLoadcalculationDialog(this);
    connect(alcd, SIGNAL(accepted()), this, SLOT(refresh()));
    alcd->exec();
}

void LoadCalculationWidget::refresh()
{
    qDebug() << __FUNCTION__;
    loadCalculationTableModel->select();
}

void LoadCalculationWidget::deleteRow()
{
    qDebug() << __FUNCTION__;

    if (DbService::getInstance()->deleteLoadCalculation(filterProxyModel->data(filterProxyModel->index(loadCalculationTableView->currentIndex().row(), 0)).toInt()))
        this->refresh();
}
