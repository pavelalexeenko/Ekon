#include "worker_widget.h"

WorkerWidget::WorkerWidget(QWidget *parent) :
    QTabWidget(parent)
{
    qDebug() << __FUNCTION__;

    disciplinesWidget = new DisciplinesWidget(this);
    this->addTab(disciplinesWidget, QString("&Дисциплины"));

    teachersWidget = new TeachersWidget(this);
    this->addTab(teachersWidget, QString("&Преподаватели"));

    groupsWidget = new GroupsWidget(this);
    this->addTab(groupsWidget, QString("&Группы"));

    flowsWidget = new FlowsWidget(this);
    this->addTab(flowsWidget, QString("П&отоки"));

    this->setStyleSheet("QTabWidget::pane { border: 0; }");
    this->tabBar()->setStyleSheet("");
}


void WorkerWidget::refresh()
{
    qDebug() << __FUNCTION__;

    disciplinesWidget->refresh();
    teachersWidget->refresh();
    groupsWidget->refresh();
    flowsWidget->refresh();
}
