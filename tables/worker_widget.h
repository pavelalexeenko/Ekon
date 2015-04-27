#ifndef WORKERWIDGET_H
#define WORKERWIDGET_H

#include <QTabWidget>
#include "tabs/disciplines_widget.h"
#include "tabs/teachers_widget.h"
#include "tabs/groups_widget.h"
#include "tabs/flows_widget.h"

class WorkerWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit WorkerWidget(QWidget *parent = 0);

public slots:
    void refresh();

private:
    DisciplinesWidget *disciplinesWidget;
    TeachersWidget *teachersWidget;
    GroupsWidget *groupsWidget;
    FlowsWidget *flowsWidget;
};

#endif // WORKERWIDGET_H
