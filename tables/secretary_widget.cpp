#include "secretary_widget.h"

SecretaryWidget::SecretaryWidget(QWidget *parent) :
    QTabWidget(parent)
  , loadCalculationWidget(new LoadCalculationWidget(this))
  , loadDistributionWidget(new LoadDistributionWidget(this))
{
    qDebug() << __FUNCTION__;

    addTab(loadCalculationWidget, QString("Распределение &дисциплин"));
    addTab(loadDistributionWidget, QString("Распределение &нагрузки"));

    setStyleSheet("QTabWidget::pane { border: 0; }");
}

void SecretaryWidget::refresh()
{
    qDebug() << __FUNCTION__;

    loadCalculationWidget->refresh();
    loadDistributionWidget->refresh();
}
