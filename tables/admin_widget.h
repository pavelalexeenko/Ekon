#ifndef ADMIN_WIDGET_H
#define ADMIN_WIDGET_H

#include <database/db_service.h>
#include <implementations/ekon_tables.h>
#include <implementations/control_widget.h>
#include <tabs/users_tab_widget.h>

#include <QTabWidget>
#include <QGridLayout>
#include <QHeaderView>

class AdminWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit AdminWidget(QWidget *parent = 0);
    void search(QString str);

public slots:
    void refresh();
    void addRow();

private:
    void addUsersTab();

private:
    QSqlRelationalTableModel *usersTableModel;
    QTableView *usersTableView;
    QSortFilterProxyModel *usersSortFilterProxyModel;

    ControlWidget *controlWidget;

};

#endif // ADMIN_WIDGET_H
