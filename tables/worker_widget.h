#ifndef WORKERWIDGET_H
#define WORKERWIDGET_H

#include <database/db_service.h>
#include <implementations/ekon_tab_widget.h>

#include <QGridLayout>
#include <QHeaderView>

class WorkerWidget : public EkonTabWidget
{
    Q_OBJECT
public:
    explicit WorkerWidget(QWidget *parent = 0);
    void search(QString str);
    void refresh();

private:
    void addDisciplinesTab();
    void addTeachersTab();
    void addGroupsTab();
    void addFlowsTab();

private:
    QSqlTableModel *disciplinesTableModel;
    QTableView *disciplinesTableView;

    QSqlTableModel *teachersTableModel;
    QTableView *teachersTableView;

    QSqlTableModel *groupsTableModel;
    QTableView *groupsTableView;

    QSqlTableModel *flowsTableModel;
    QTableView *flowsTableView;
};

#endif // WORKERWIDGET_H
