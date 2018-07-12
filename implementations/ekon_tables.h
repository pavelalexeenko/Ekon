#ifndef EKONTABWIDGET_H
#define EKONTABWIDGET_H

#include <database/db_service.h>

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlQueryModel>
#include <QSqlRelationalDelegate>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QHeaderView>
#include <QList>
#include <QPair>
#include "implementations/checkable_sort_filter_proxy_model.h"

class EkonTables
{
public:
    EkonTables();

    static QSqlTableModel* createTableModel(QWidget* parentWidget, QString tableName, QStringList columnNames);
    static QSqlRelationalTableModel* createRelationalTableModel(QWidget* parentWidget, QString tableName, QStringList columnNames, QList<QPair<int, QSqlRelation> > relations);

    static QTableView* createTableView(QWidget* parentWidget, QSqlTableModel* model);
    static QTableView* createTableView(QWidget* parentWidget, QSqlQueryModel* model);
    static QTableView* createTableView(QWidget* parentWidget, CheckableSortFilterProxyModel* model);
    static QTableView* createRelationTableView(QWidget* parentWidget, QSqlRelationalTableModel* model);

private:
    static void configureTableModel(QSqlTableModel* tableModel, QStringList columnNames);
    static void configureTableView(QTableView* tableView);
};

#endif // EKONTABWIDGET_H
