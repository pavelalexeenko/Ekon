#ifndef LOADCALCULATIONWIDGET_H
#define LOADCALCULATIONWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <implementations/control_widget.h>
#include <implementations/ekon_tables.h>

class LoadCalculationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoadCalculationWidget(QWidget *parent = 0);

public slots:
    void addRow();
    void refresh();

private:
    QSqlTableModel *loadCalculationTableModel;
    QTableView *loadCalculationTableView;

    ControlWidget *controlWidget;
};

#endif // LOADCALCULATIONWIDGET_H
