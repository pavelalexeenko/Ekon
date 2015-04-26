#ifndef USERS_TAB_WIDGET_H
#define USERS_TAB_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <implementations/control_widget.h>
#include <implementations/ekon_tables.h>

#include <QDebug>

class UsersTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UsersTabWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void addRow();
    void refresh();

private:
    QSqlRelationalTableModel *usersTableModel;
    QTableView *usersTableView;
    QSortFilterProxyModel *usersSortFilterProxyModel;

    ControlWidget *controlWidget;
};

#endif // USERS_TAB_WIDGET_H
