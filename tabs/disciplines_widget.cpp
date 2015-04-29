#include "disciplines_widget.h"
#include "dialogs/add_discipline_dialog.h"

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

    controlWidget = new ControlWidget(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(disciplinesTableView);
    layout->addWidget(controlWidget);

    this->setLayout(layout);

    connect(controlWidget, SIGNAL(addRow()), this, SLOT(addRow()));
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

