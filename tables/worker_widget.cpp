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
    this->tabBar()->setStyleSheet("QTabBar::tab {"
                                           "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                                        "stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,"
                                                                        "stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);"
                                            "border: 2px solid #C4C4C3;"
                                            "border-bottom-color: #C2C7CB;"
                                            "border-top-left-radius: 4px;"
                                            "border-top-right-radius: 4px;"
                                            "min-width: 8ex;"
                                            "padding: 2px;"
                                        "}");
}


void WorkerWidget::refresh()
{
    qDebug() << __FUNCTION__;

    disciplinesWidget->refresh();
    teachersWidget->refresh();
    groupsWidget->refresh();
    flowsWidget->refresh();
}
