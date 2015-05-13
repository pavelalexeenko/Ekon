#include "worker_widget.h"

WorkerWidget::WorkerWidget(QWidget *parent) :
    QTabWidget(parent)
  , disciplinesWidget(new DisciplinesWidget(this))
  , groupsWidget(new GroupsWidget(this))
  , teachersWidget(new TeachersWidget(this))
  , flowsWidget(new FlowsWidget(this))
{
    qDebug() << __FUNCTION__;

    addTab(disciplinesWidget, QString("&Дисциплины"));
    addTab(teachersWidget, QString("&Преподаватели"));
    addTab(groupsWidget, QString("&Группы"));
    addTab(flowsWidget, QString("П&отоки"));

    setStyleSheet("QTabWidget::pane { border: 0; }");
    tabBar()->setStyleSheet("");
}

void WorkerWidget::refresh()
{
    qDebug() << __FUNCTION__;

    disciplinesWidget->refresh();
    teachersWidget->refresh();
    groupsWidget->refresh();
    flowsWidget->refresh();
}
