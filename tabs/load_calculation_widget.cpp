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
                << "Экзамен"
                << "Зачет"
                << "Текущая консультации"
                << "Ознакомительная практика"
                << "Преддипломная практика"
                << "Курсовая работа"
                << "Управляемая самост. работа"
                << "Контрольная работа"
                << "Дипломное проектирование"
                << "Рук-во аспирантами"
                << "Гос экзамен"
                << "ГЭК"
                << "Руководство кафедрой"
                << "УИРС";

    loadCalculationQueryModel = new QSqlQueryModel(this);
    loadCalculationQueryModel->setQuery("select * from VIEW_LOAD_CALCULATION");

    for (int i = 0; i < columnNames.length(); i++)
        loadCalculationQueryModel->setHeaderData(i, Qt::Horizontal, columnNames.at(i));

    loadCalculationTableView = EkonTables::createTableView(this, loadCalculationQueryModel);

    loadCalculationTableView->setStyleSheet("QModelIndex::section {background-color:grey}");
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

    AddLoadcalculationDialog *alcd = new AddLoadcalculationDialog(this);
    connect(alcd, SIGNAL(accepted()), this, SLOT(refresh()));
    alcd->exec();
}

void LoadCalculationWidget::refresh()
{
    qDebug() << __FUNCTION__;
    loadCalculationQueryModel->setQuery("select * from VIEW_LOAD_CALCULATION");
}
