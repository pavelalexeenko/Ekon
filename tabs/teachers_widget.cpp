#include "teachers_widget.h"
#include "dialogs/add_teacher_dialog.h"

TeachersWidget::TeachersWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << __FUNCTION__;

    QStringList columnNames;
    columnNames << "ID"
                << "ФИО"
                << "Ставка"
                << "Примечание";

    teachersTableModel = EkonTables::createTableModel(this, "DRT_TEACHERS", columnNames);
    teachersTableView = EkonTables::createTableView(this, teachersTableModel);

    controlWidget = new ControlWidget(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(teachersTableView);
    layout->addWidget(controlWidget);

    this->setLayout(layout);

    connect(controlWidget, SIGNAL(addRow()), this, SLOT(addRow()));
    connect(controlWidget, SIGNAL(removeRow()), this, SLOT(deleteRow()));
}

void TeachersWidget::addRow()
{
    qDebug() << __FUNCTION__;
    AddTeacherDialog *atd = new AddTeacherDialog(this);
    connect(atd, SIGNAL(accepted()), this, SLOT(refresh()));
    atd->exec();
}

void TeachersWidget::refresh()
{
    qDebug() << __FUNCTION__;
    teachersTableModel->select();
}

void TeachersWidget::deleteRow()
{
    qDebug() << __FUNCTION__;

    if (DbService::getInstance()->deleteTeacher(teachersTableModel->data(teachersTableModel->index(teachersTableView->currentIndex().row(), 0)).toInt()))
        this->refresh();
}
