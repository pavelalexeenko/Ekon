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
    void deleteRow(const QModelIndex& index);
    void refresh();
    void editRow(const QModelIndex &index);

private:
    QSqlTableModel *flowsTableModel;
    QTableView *flowsTableView;

    ControlWidget *controlWidget;
};

#endif // FLOWSTABWIDGET_H
