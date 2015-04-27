#ifndef FLOWSTABWIDGET_H
#define FLOWSTABWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <implementations/control_widget.h>
#include <implementations/ekon_tables.h>

#include <QDebug>

class FlowsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlowsWidget(QWidget *parent = 0);

public slots:
    void addRow();
    void refresh();

private:
    QSqlTableModel *flowsTableModel;
    QTableView *flowsTableView;

    ControlWidget *controlWidget;
};

#endif // FLOWSTABWIDGET_H
