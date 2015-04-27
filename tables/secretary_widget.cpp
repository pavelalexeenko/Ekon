#include "secretary_widget.h"

SecretaryWidget::SecretaryWidget(QWidget *parent) :
    QTabWidget(parent)
{
    qDebug() << __FUNCTION__;

    loadCalculationWidget = new LoadCalculationWidget(this);
    this->addTab(loadCalculationWidget, QString("Распределение &дисциплин"));

    loadDistributionWidget = new LoadDistributionWidget(this);
    this->addTab(loadDistributionWidget, QString("Распределение &нагрузки"));

    this->setStyleSheet("QTabWidget::pane { border: 0; }");
}

void SecretaryWidget::refresh()
{
    qDebug() << __FUNCTION__;

    loadCalculationWidget->refresh();
    loadDistributionWidget->refresh();
}
