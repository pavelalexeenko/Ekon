#ifndef DISCIPLINESTABWIDGET_H
#define DISCIPLINESTABWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <implementations/control_widget.h>
#include <implementations/ekon_tables.h>

#include <QDebug>
#include <QSqlQuery>

class DisciplinesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DisciplinesWidget(QWidget *parent = 0);

public slots:
    void addRow();
    void search(QString str);
    void refresh();

private:
    QSqlTableModel *disciplinesTableModel;
    QTableView *disciplinesTableView;

    ControlWidget *controlWidget;
};

#endif // DISCIPLINESTABWIDGET_H
