#include "disciplines_widget.h"
#include "dialogs/add_discipline_dialog.h"
#include "implementations/check_box_delegate.h"
#include "implementations/checkable_sort_filter_proxy_model.h"

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

    CheckableSortFilterProxyModel *cfpm = new CheckableSortFilterProxyModel(this);
    QList<int> boolCols;
    for (int i = 5; i < 20; i++)
        boolCols.append(i);

    cfpm->setParameters(boolCols, QList<int>(), QList<int>());
    cfpm->setSourceModel(disciplinesTableModel);

    disciplinesTableView = EkonTables::createTableView(this, disciplinesTableModel);
    disciplinesTableView->setModel(cfpm);

    controlWidget = new ControlWidget(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(disciplinesTableView);
    layout->addWidget(controlWidget);

    this->setLayout(layout);

    connect(controlWidget, SIGNAL(addRow()), this, SLOT(addRow()));
    connect(controlWidget, SIGNAL(search(QString)), this, SLOT(search(QString)));
    connect(controlWidget, SIGNAL(removeRow()), this, SLOT(deleteRow()));
}

void DisciplinesWidget::addRow()
{
    qDebug() << __FUNCTION__;
    AddDisciplineDialog *add = new AddDisciplineDialog(this);
    connect(add, SIGNAL(accepted()), this, SLOT(refresh()));
    add->exec();
}

void DisciplinesWidget::search(QString str)
{
    qDebug() << __FUNCTION__ << "  " << str;

    for (int i = 0; i < disciplinesTableModel->rowCount(); i++)
        for (int j = 0; j < disciplinesTableModel->columnCount(); j++)
        {
         //   if (disciplinesTableModel->index(i,j).data().toString().contains(str.trimmed()))
            //    disciplinesTableView->back
            ;
        }
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

