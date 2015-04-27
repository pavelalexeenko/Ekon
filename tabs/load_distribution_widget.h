#ifndef LOADDISTRIBUTIONWIDGET_H
#define LOADDISTRIBUTIONWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <implementations/control_widget.h>
#include <implementations/ekon_tables.h>

class LoadDistributionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoadDistributionWidget(QWidget *parent = 0);

public slots:
    void addRow();
    void refresh();

private:
    QSqlRelationalTableModel *loadDistributionTableModel;
    QTableView *loadDistributionTableView;

    ControlWidget *controlWidget;
};

#endif // LOADDISTRIBUTIONWIDGET_H
