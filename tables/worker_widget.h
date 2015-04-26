#ifndef WORKERWIDGET_H
#define WORKERWIDGET_H

#include <database/db_service.h>
#include <implementations/ekon_tables.h>

#include <QTabWidget>
#include <QGridLayout>
#include <QHeaderView>

class WorkerWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit WorkerWidget(QWidget *parent = 0);
    void search(QString str);

public slots:
    void refresh();
    void addRow();

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
