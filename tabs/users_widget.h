#ifndef USERS_TAB_WIDGET_H
#define USERS_TAB_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <implementations/control_widget.h>
#include <implementations/ekon_tables.h>

#include <QDebug>

class UsersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UsersWidget(QWidget *parent = 0);

public slots:
    void addRow();
    void refresh();
    void deleteRow();

private:
    QSqlRelationalTableModel *usersTableModel;
    QTableView *usersTableView;

    ControlWidget *controlWidget;
};

#endif // USERS_TAB_WIDGET_H
