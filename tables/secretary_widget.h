#ifndef SECRETARY_WIDGET_H
#define SECRETARY_WIDGET_H

#include <QTabWidget>
#include "tabs/load_calculation_widget.h"
#include "tabs/load_distribution_widget.h"

class SecretaryWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit SecretaryWidget(QWidget *parent = 0);

public slots:
    void refresh();

private:
    LoadCalculationWidget *loadCalculationWidget;
    LoadDistributionWidget *loadDistributionWidget;
};

#endif // SECRETARY_WIDGET_H
