#include "manager_widget.h"

ManagerWidget::ManagerWidget(QWidget *parent) :
    QTabWidget(parent)

  , teachersWidget(new TeachersWidget(this))
  , loadDistributionWidget(new LoadDistributionWidget(this))
{
    qDebug() << __FUNCTION__;

    addTab(teachersWidget, QString("&Преподаватели"));
    addTab(loadDistributionWidget, QString("Распределение &нагрузки"));

    setStyleSheet("QTabWidget::pane { border: 0; }");
}

void ManagerWidget::refresh()
{
    qDebug() << __FUNCTION__;

    teachersWidget->refresh();
    loadDistributionWidget->refresh();
}
