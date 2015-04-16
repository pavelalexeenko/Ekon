#ifndef SECRETARY_WIDGET_H
#define SECRETARY_WIDGET_H

#include <database/db_service.h>
#include <implementations/ekon_tab_widget.h>

#include <QGridLayout>
#include <QHeaderView>

class SecretaryWidget : public EkonTabWidget
{
    Q_OBJECT
public:
    explicit SecretaryWidget(QWidget *parent = 0);
    void search(QString str);
    void refresh();

private:
    void addUsersTab();
    void addDisciplinesTab();
    void addTeachersTab();

private:
    QSqlRelationalTableModel *usersTableModel;
    QTableView *usersTableView;

    QSqlTableModel *disciplinesTableModel;
    QTableView *disciplinesTableView;

    QSqlTableModel *teachersTableModel;
    QTableView *teachersTableView;

};

#endif // SECRETARY_WIDGET_H
