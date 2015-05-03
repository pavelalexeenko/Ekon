#include "disciplines_widget.h"
#include "dialogs/add_discipline_dialog.h"
#include "implementations/check_box_delegate.h"

DisciplinesWidget::DisciplinesWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << __FUNCTION__;

    QStringList columnNames;
    columnNames << "ID"
                << "Название дисциплины"
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

    disciplinesTableModel = EkonTables::createTableModel(this, "DRT_DISCIPLINES", columnNames);
    disciplinesTableView = EkonTables::createTableView(this, disciplinesTableModel);

    disciplinesTableView->setItemDelegateForColumn(5, new CheckBoxDelegate());
    disciplinesTableView->setItemDelegateForColumn(6, new CheckBoxDelegate());
    disciplinesTableView->setItemDelegateForColumn(7, new CheckBoxDelegate());
    disciplinesTableView->setItemDelegateForColumn(8, new CheckBoxDelegate());
    disciplinesTableView->setItemDelegateForColumn(9, new CheckBoxDelegate());
    disciplinesTableView->setItemDelegateForColumn(10, new CheckBoxDelegate());
    disciplinesTableView->setItemDelegateForColumn(11, new CheckBoxDelegate());
    disciplinesTableView->setItemDelegateForColumn(12, new CheckBoxDelegate());
    disciplinesTableView->setItemDelegateForColumn(13, new CheckBoxDelegate());
    disciplinesTableView->setItemDelegateForColumn(14, new CheckBoxDelegate());
    disciplinesTableView->setItemDelegateForColumn(15, new CheckBoxDelegate());
    disciplinesTableView->setItemDelegateForColumn(16, new CheckBoxDelegate());
    disciplinesTableView->setItemDelegateForColumn(17, new CheckBoxDelegate());
    disciplinesTableView->setItemDelegateForColumn(18, new CheckBoxDelegate());
    disciplinesTableView->setItemDelegateForColumn(19, new CheckBoxDelegate());

    controlWidget = new ControlWidget(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(disciplinesTableView);
    layout->addWidget(controlWidget);

    this->setLayout(layout);

    connect(controlWidget, SIGNAL(addRow()), this, SLOT(addRow()));
    connect(controlWidget, SIGNAL(search(QString)), this, SLOT(search(QString)));
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

