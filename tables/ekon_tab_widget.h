#ifndef EKONTABWIDGET_H
#define EKONTABWIDGET_H

#include <database/db_service.h>

#include <QWidget>
#include <QTabWidget>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QHeaderView>
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

public:
    QSqlTableModel* createTableModel(QWidget* parentWidget, QString tableName, QStringList columnNames);
    QSqlRelationalTableModel *createRelationalTableModel(QWidget* parentWidget, QString tableName, QStringList columnNames, QPair<int, QSqlRelation> relations);

    QTableView* createTableView(QWidget* parentWidget, QSqlTableModel* model);
};

#endif // EKONTABWIDGET_H
