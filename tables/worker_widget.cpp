#include "worker_widget.h"

WorkerWidget::WorkerWidget(QWidget *parent) :
    EkonTabWidget(parent)
{
    addDisciplinesTab();
    addTeachersTab();
    addGroupsTab();
}

void WorkerWidget::search(QString str)
{
    qDebug() << "WorkerWidget::search(QString \"" + str + "\")";
}

void WorkerWidget::refresh()
{
    qDebug() << "WorkerWidget::refresh()";

}

void WorkerWidget::addDisciplinesTab()
{
    QStringList columnNames;
    columnNames << "ID"
                << "Название дисциплины"
                << "Лекции"
                << "Практики";

    QWidget *widget = new QWidget();
    disciplinesTableModel = createTableModel(widget, "DRT_DISCIPLINES", columnNames);
    disciplinesTableView = createTableView(widget, disciplinesTableModel);

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(disciplinesTableView);

    this->addTab(widget, QString("Дисциплины"));
}

void WorkerWidget::addTeachersTab()
{
    QStringList columnNames;
    columnNames << "ID"
                << "Название дисциплины"
                << "Лекции"
                << "Практики";

    QWidget *widget = new QWidget();
    teachersTableModel = createTableModel(widget, "DRT_TEACHERS", columnNames);
    teachersTableView = createTableView(widget, teachersTableModel);

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(teachersTableView);

    this->addTab(widget, QString("Преподаватели"));
}

void WorkerWidget::addGroupsTab()
{
    QStringList columnNames;
    columnNames << "ID"
                << "Название"
                << "Количество студентов"
                << "Курс";

    QWidget *widget = new QWidget();
    groupsTableModel = createTableModel(widget, "DRT_GROUPS", columnNames);
    groupsTableView = createTableView(widget, groupsTableModel);

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(groupsTableView);

    this->addTab(widget, QString("Группы"));
}