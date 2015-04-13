#ifndef SECRETARY_WIDGET_H
#define SECRETARY_WIDGET_H

#include <database/db_service.h>

#include <QTabWidget>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QTableView>
#include <QGridLayout>
#include <QHeaderView>

class SecretaryWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit SecretaryWidget(QWidget *parent = 0);

private:
    void addUsersTab();
    void addDisciplinesTab();
    void addTeachersTab();

private:
    QSqlRelationalTableModel *_usersTableModel;
    QTableView *_usersTableView;

    QSqlTableModel *_disciplinesTableModel;
    QTableView *_disciplinesTableView;

    QSqlTableModel *_teachersTableModel;
    QTableView *_teachersTableView;

};

#endif // SECRETARY_WIDGET_H
