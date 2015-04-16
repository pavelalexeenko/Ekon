#ifndef EKONTABWIDGET_H
#define EKONTABWIDGET_H

#include <database/db_service.h>
#include <implementations/freeze_table_widget.h>

#include <QWidget>
#include <QTabWidget>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QHeaderView>
#include <QList>
#include <QPair>

class EkonTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit EkonTabWidget(QWidget *parent = 0);

signals:

public slots:  

private:
    void configureTableModel(QSqlTableModel* tableModel, QString tableName, QStringList columnNames);
    void configureTableView(FreezeTableWidget* tableView);

public:
    QSqlTableModel* createTableModel(QWidget* parentWidget, QString tableName, QStringList columnNames);
    QSqlRelationalTableModel* createRelationalTableModel(QWidget* parentWidget, QString tableName, QStringList columnNames, QList<QPair<int, QSqlRelation> > relations);

    FreezeTableWidget* createTableView(QWidget* parentWidget, QSqlTableModel* model);
    FreezeTableWidget* createRelationTableView(QWidget* parentWidget, QSqlRelationalTableModel* model);
};

#endif // EKONTABWIDGET_H
