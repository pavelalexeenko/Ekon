#include "worker_widget.h"
#include "implementations/checkbox_item_delegate.h"
#include <dialogs/add_teacher_dialog.h>
#include <dialogs/add_discipline_dialog.h>

WorkerWidget::WorkerWidget(QWidget *parent) :
    QTabWidget(parent)
{
    addDisciplinesTab();
    addTeachersTab();
    addGroupsTab();
    addFlowsTab();
}

void WorkerWidget::search(QString str)
{
    qDebug() << "WorkerWidget::search(QString \"" + str + "\")";
}

void WorkerWidget::refresh()
{
    qDebug() << "WorkerWidget::refresh()";
    disciplinesTableModel->select();
    teachersTableModel->select();
    groupsTableModel->select();
    flowsTableModel->select();
}

void WorkerWidget::addRow()
{
    qDebug() << "WorkerWidget::addRow()";

    AddTeacherDialog *atd = new AddTeacherDialog(this);
    connect(atd, SIGNAL(accepted()), this, SLOT(refresh()));

    AddDisciplineDialog *add = new AddDisciplineDialog(this);
    connect(add, SIGNAL(accepted()), this, SLOT(refresh()));

    switch (this->currentIndex()){
    case 0:
        add->show();
        break;
    case 1:
        atd->show();
        break;
    default:
        break;
    }
}

void WorkerWidget::addDisciplinesTab()
{
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

    QWidget *widget = new QWidget();
    disciplinesTableModel = EkonTables::createTableModel(widget, "DRT_DISCIPLINES", columnNames);
    disciplinesTableView = EkonTables::createTableView(widget, disciplinesTableModel);
    disciplinesTableView->setItemDelegateForColumn(5, new CheckBoxItemDelegate());
    disciplinesTableView->setItemDelegateForColumn(6, new CheckBoxItemDelegate());
    disciplinesTableView->setItemDelegateForColumn(7, new CheckBoxItemDelegate());
    disciplinesTableView->setItemDelegateForColumn(8, new CheckBoxItemDelegate());
    disciplinesTableView->setItemDelegateForColumn(9, new CheckBoxItemDelegate());

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(disciplinesTableView);

    this->addTab(widget, QString("Дисциплины"));
}

void WorkerWidget::addTeachersTab()
{
    QStringList columnNames;
    columnNames << "ID"
                << "ФИО"
                << "Ставка"
                << "Примечание";

    QWidget *widget = new QWidget();
    teachersTableModel = EkonTables::createTableModel(widget, "DRT_TEACHERS", columnNames);
    teachersTableView = EkonTables::createTableView(widget, teachersTableModel);

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
                << "Курс"
                << "Количество подгрупп"
                << "Семестр"
                << "Факультет"
                << "Специальность"
                << "Примечание";

    QWidget *widget = new QWidget();
    groupsTableModel = EkonTables::createTableModel(widget, "DRT_GROUPS", columnNames);
    groupsTableView = EkonTables::createTableView(widget, groupsTableModel);

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(groupsTableView);

    this->addTab(widget, QString("Группы"));
}

void WorkerWidget::addFlowsTab()
{
    QStringList columnNames;
    columnNames << "ID"
                << "Название потока"
                << "Список групп";

    QWidget *widget = new QWidget();
    flowsTableModel = EkonTables::createTableModel(widget, "VIEW_FLOWS", columnNames);
    flowsTableView = EkonTables::createTableView(widget, flowsTableModel);
    flowsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(flowsTableView);

    this->addTab(widget, QString("Потоки"));
}
