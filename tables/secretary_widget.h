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

public slots:
    void refresh();
    void addRow();

private:
    void addLoadCalculationTab();
    void addLoadDistributionTab();

private:

    QSqlRelationalTableModel *loadCalculationTableModel;
    QTableView *loadCalculationTableView;

    QSqlRelationalTableModel *loadDistributionTableModel;
    QTableView *loadDistributionTableView;

};

#endif // SECRETARY_WIDGET_H
