#ifndef SECRETARY_WIDGET_H
#define SECRETARY_WIDGET_H

#include <QTabWidget>
#include "tabs/teachers_widget.h"
#include "tabs/load_distribution_widget.h"

class ManagerWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit ManagerWidget(QWidget *parent = 0);

public slots:
    void refresh();

private:
    TeachersWidget *teachersWidget;
    LoadDistributionWidget *loadDistributionWidget;
};

#endif // SECRETARY_WIDGET_H
