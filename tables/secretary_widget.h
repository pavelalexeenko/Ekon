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
    void addLoadCalculationTab();
    void addLoadDistributionTab();

private:
    QSqlRelationalTableModel *usersTableModel;
    QTableView *usersTableView;

    QSqlRelationalTableModel *loadCalculationTableModel;
    QTableView *loadCalculationTableView;

    QSqlRelationalTableModel *loadDistributionTableModel;
    QTableView *loadDistributionTableView;

};

#endif // SECRETARY_WIDGET_H
