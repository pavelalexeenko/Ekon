#include "secretary_widget.h"

SecretaryWidget::SecretaryWidget(QWidget *parent) :
    QTabWidget(parent)
  , disciplinesWidget(new DisciplinesWidget(this))
  , groupsWidget(new GroupsWidget(this))
  , flowsWidget(new FlowsWidget(this))
  , loadCalculationWidget(new LoadCalculationWidget(this))
{
    qDebug() << __FUNCTION__;

    addTab(disciplinesWidget, QString("&Дисциплины"));
    addTab(groupsWidget, QString("&Группы"));
    addTab(flowsWidget, QString("П&отоки"));
    addTab(loadCalculationWidget, QString("Распределение &дисциплин"));

    setStyleSheet("QTabWidget::pane { border: 0; }");
    tabBar()->setStyleSheet("");
}

void SecretaryWidget::refresh()
{
    qDebug() << __FUNCTION__;

    disciplinesWidget->refresh();
    groupsWidget->refresh();
    flowsWidget->refresh();
    loadCalculationWidget->refresh();
}
