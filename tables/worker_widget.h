#ifndef WORKERWIDGET_H
#define WORKERWIDGET_H

#include <database/db_service.h>

#include <QTabWidget>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QTableView>
#include <QGridLayout>
#include <QHeaderView>

class WorkerWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit WorkerWidget(QWidget *parent = 0);

private:
    void addDisciplinesTab();
    void addTeachersTab();

private:
    QSqlTableModel *_disciplinesTableModel;
    QTableView *_disciplinesTableView;

    QSqlTableModel *_teachersTableModel;
    QTableView *_teachersTableView;
};

#endif // WORKERWIDGET_H
