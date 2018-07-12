#ifndef WORKERWIDGET_H
#define WORKERWIDGET_H

#include <QTabWidget>
#include "tabs/disciplines_widget.h"
#include "tabs/groups_widget.h"
#include "tabs/flows_widget.h"
#include "tabs/load_calculation_widget.h"

class SecretaryWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit SecretaryWidget(QWidget *parent = 0);

public slots:
    void refresh();

private:
    DisciplinesWidget *disciplinesWidget;
    GroupsWidget *groupsWidget;
    FlowsWidget *flowsWidget;
    LoadCalculationWidget *loadCalculationWidget;
};

#endif // WORKERWIDGET_H
