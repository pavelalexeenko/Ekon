#ifndef LOADCALCULATIONWIDGET_H
#define LOADCALCULATIONWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <implementations/control_widget.h>
#include <implementations/ekon_tables.h>
#include "implementations/checkable_sort_filter_proxy_model.h"

class LoadCalculationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoadCalculationWidget(QWidget *parent = 0);

public slots:
    void addRow();
    void refresh();

private slots:
    void deleteRow();

private:
    QSqlTableModel *loadCalculationTableModel;
    CheckableSortFilterProxyModel *filterProxyModel;
    QTableView *loadCalculationTableView;

    ControlWidget *controlWidget;
};

#endif // LOADCALCULATIONWIDGET_H
