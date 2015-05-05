#ifndef GROUPSTABWIDGET_H
#define GROUPSTABWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <implementations/control_widget.h>
#include <implementations/ekon_tables.h>

#include <QDebug>

class GroupsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GroupsWidget(QWidget *parent = 0);

public slots:
    void addRow();
    void refresh();
    void deleteRow();

private:
    QSqlTableModel *groupsTableModel;
    QTableView *groupsTableView;

    ControlWidget *controlWidget;
};

#endif // GROUPSTABWIDGET_H
