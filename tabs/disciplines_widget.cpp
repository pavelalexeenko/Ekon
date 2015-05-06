#include "disciplines_widget.h"
#include "dialogs/add_discipline_dialog.h"
#include "implementations/check_box_delegate.h"

DisciplinesWidget::DisciplinesWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << __FUNCTION__;

    QStringList columnNames;
    columnNames << "ID"
                << "Название\n дисциплины"
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

    disciplinesTableModel = EkonTables::createTableModel(this, "DRT_DISCIPLINES", columnNames);

    filterProxyModel = new CheckableSortFilterProxyModel(this);
    QList<int> boolCols;
    for (int i = 5; i < 20; i++)
        boolCols.append(i);
    filterProxyModel->setParameters(boolCols, QList<int>(), QList<int>());
    filterProxyModel->setSourceModel(disciplinesTableModel);

    disciplinesTableView = EkonTables::createTableView(this, filterProxyModel);

    controlWidget = new ControlWidget(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(disciplinesTableView);
    layout->addWidget(controlWidget);

    this->setLayout(layout);

    connect(controlWidget, SIGNAL(addRow()), this, SLOT(addRow()));
    connect(controlWidget, SIGNAL(removeRow()), this, SLOT(deleteRow()));
    connect(controlWidget, SIGNAL(filter(QString)), filterProxyModel, SLOT(setFilterFixedString(QString)));
    connect(controlWidget, SIGNAL(search(QString)), this, SLOT(search(QString)));

}

void DisciplinesWidget::addRow()
{
    qDebug() << __FUNCTION__;
    AddDisciplineDialog *add = new AddDisciplineDialog(this);
    connect(add, SIGNAL(accepted()), this, SLOT(refresh()));
    add->exec();
}

void DisciplinesWidget::refresh()
{
    qDebug() << __FUNCTION__;
    disciplinesTableModel->select();
}

void DisciplinesWidget::deleteRow()
{
    qDebug() << __FUNCTION__;

    if (DbService::getInstance()->deleteDiscipline(disciplinesTableModel->data(disciplinesTableModel->index(disciplinesTableView->currentIndex().row(), 0)).toInt()))
        this->refresh();
}

void DisciplinesWidget::search(QString str)
{
    filterProxyModel->setColorFilterString(str);
    disciplinesTableView->reset();
}

