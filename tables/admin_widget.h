#ifndef ADMIN_WIDGET_H
#define ADMIN_WIDGET_H

#include <database/db_service.h>

#include <QTabWidget>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QGridLayout>
#include <QHeaderView>

class AdminWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit AdminWidget(QWidget *parent = 0);
    void search(QString str);

private:
    void addUsersTab();

private:
    QSqlRelationalTableModel *usersTableModel;
    QTableView *usersTableView;
    QSortFilterProxyModel *usersSortFilterProxyModel;

};

#endif // ADMIN_WIDGET_H
