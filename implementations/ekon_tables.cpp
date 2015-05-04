#include "ekon_tables.h"

EkonTables::EkonTables()
{
}

void EkonTables::configureTableModel(QSqlTableModel *tableModel, QStringList columnNames)
{
    tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    for (int i = 0; i < columnNames.length(); i++)
    {
        tableModel->setHeaderData(i, Qt::Horizontal, columnNames.at(i));
    }

    tableModel->select();
}

void EkonTables::configureTableView(QTableView *tableView)
{
    Q_UNUSED(tableView);
}

QSqlTableModel* EkonTables::createTableModel(QWidget *parentWidget, QString tableName, QStringList columnNames)
{ 
    QSqlTableModel *tableModel = new QSqlTableModel(parentWidget, DbService::getInstance()->getCurrentDatabase());
    tableModel->setTable(tableName);
    configureTableModel(tableModel, columnNames);
    return tableModel;
}

QSqlRelationalTableModel* EkonTables::createRelationalTableModel(QWidget *parentWidget, QString tableName, QStringList columnNames, QList<QPair<int, QSqlRelation> > relations)
{
    QSqlRelationalTableModel *tableModel = new QSqlRelationalTableModel(parentWidget, DbService::getInstance()->getCurrentDatabase());
    tableModel->setTable(tableName);

    for (auto relation : relations)
        tableModel->setRelation(relation.first, relation.second);

    configureTableModel(tableModel, columnNames);

    return tableModel;
}

QTableView* EkonTables::createTableView(QWidget* parentWidget, QSqlTableModel* model)
{
    QTableView *tableView = new QTableView(parentWidget);
    tableView->setModel(model);
    tableView->hideColumn(0);
    tableView->show();
    tableView->setSortingEnabled(true);
    tableView->setDragEnabled(true);
   // tableView->setStyleSheet("QHeaderView::section {background-color:grey}");
   // tableView->verticalHeader()->hide();
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    return tableView;
}

QTableView *EkonTables::createTableView(QWidget *parentWidget, QSqlQueryModel *model)
{
    QTableView *tableView = new QTableView(parentWidget);
    tableView->setModel(model);
    tableView->hideColumn(0);
    tableView->show();
    tableView->setSortingEnabled(true);
    tableView->setDragEnabled(true);
   // tableView->setStyleSheet("QHeaderView::section {background-color:grey}");
   // tableView->verticalHeader()->hide();
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    return tableView;
}

QTableView* EkonTables::createRelationTableView(QWidget *parentWidget, QSqlRelationalTableModel *model)
{
    QTableView *tableView = createTableView(parentWidget, model);
    tableView->setItemDelegate(new QSqlRelationalDelegate(tableView));

    return tableView;
}
