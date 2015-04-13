#ifndef WORKER_WIDGET_H
#define WORKER_WIDGET_H

#include <database/db_service.h>

#include <QTabWidget>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QGridLayout>
#include <QHeaderView>

class WorkerWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit WorkerWidget(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    void addDisciplinesTab();
    void addTeachersTab();

private:
    QSqlTableModel *_disciplinesTableModel;
    QTableView *_disciplinesTableView;

    QSqlTableModel *_teachersTableModel;
    QTableView *_teachersTableView;
    
};

#endif // WORKER_WIDGET_H
