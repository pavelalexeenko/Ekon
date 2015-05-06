#include "load_calculation_widget.h"
#include "dialogs/add_loadcalculation_dialog.h"
#include "implementations/read_only_delegate.h"
#include "implementations/checkable_sort_filter_proxy_model.h"

LoadCalculationWidget::LoadCalculationWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << __FUNCTION__;

    QStringList columnNames;
    columnNames << "ID"
                << "Название\n дисциплины"
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

    CheckableSortFilterProxyModel *cfpm = new CheckableSortFilterProxyModel(this);
    QList<int> readonlyCols;
    for (int i = 5; i < 21; i++)
        readonlyCols.append(i);

    cfpm->setParameters(QList<int>(), readonlyCols, QList<int>());
    cfpm->setSourceModel(loadCalculationTableModel);

    loadCalculationTableView = EkonTables::createTableView(this, cfpm);

    //loadCalculationTableView->setStyleSheet("QTableView::item {background-color: #D4D0C8; color: black;}");
    controlWidget = new ControlWidget(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(loadCalculationTableView);
    layout->addWidget(controlWidget);

    this->setLayout(layout);

    connect(controlWidget, SIGNAL(addRow()), this, SLOT(addRow()));
    connect(controlWidget, SIGNAL(removeRow()), this, SLOT(deleteRow()));
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

    if (DbService::getInstance()->deleteLoadCalculation(loadCalculationTableModel->data(loadCalculationTableModel->index(loadCalculationTableView->currentIndex().row(), 0)).toInt()))
        this->refresh();
}
