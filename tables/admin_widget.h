#ifndef ADMIN_WIDGET_H
#define ADMIN_WIDGET_H

#include <database/db_service.h>
#include <implementations/ekon_tab_widget.h>

#include <QGridLayout>
#include <QHeaderView>

class AdminWidget : public EkonTabWidget
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

};

#endif // ADMIN_WIDGET_H
