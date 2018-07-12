#ifndef TEACHERSTABWIDGET_H
#define TEACHERSTABWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <implementations/control_widget.h>
#include <implementations/ekon_tables.h>

#include <QDebug>

class TeachersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TeachersWidget(QWidget *parent = 0);

public slots:
    void addRow();
    void refresh();
    void deleteRow();

private:
    QSqlTableModel *teachersTableModel;
    CheckableSortFilterProxyModel *filterProxyModel;
    QTableView *teachersTableView;

    ControlWidget *controlWidget;
};

#endif // TEACHERSTABWIDGET_H
