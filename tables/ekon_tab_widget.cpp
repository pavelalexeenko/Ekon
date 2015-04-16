#include "ekon_tab_widget.h"

EkonTabWidget::EkonTabWidget(QWidget *parent) : QTabWidget(parent)
{

}

void EkonTabWidget::configureTableModel(QSqlTableModel *tableModel, QString tableName, QStringList columnNames)
{
    tableModel->setTable(tableName);
    tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    for (int i = 0; i < columnNames.length(); i++)
    {
        tableModel->setHeaderData(i, Qt::Horizontal, columnNames.at(i));
    }

    tableModel->select();
}

QSqlTableModel* EkonTabWidget::createTableModel(QWidget *parentWidget, QString tableName, QStringList columnNames)
{ 
    QSqlTableModel *tableModel = new QSqlTableModel(parentWidget, DbService::getInstance()->getCurrentDatabase());
    configureTableModel(tableModel, tableName, columnNames);
    return tableModel;
}

QSqlRelationalTableModel *EkonTabWidget::createRelationalTableModel(QWidget *parentWidget, QString tableName, QStringList columnNames, QPair<int, QSqlRelation> relations)
{
    QSqlRelationalTableModel *tableModel = new QSqlRelationalTableModel(parentWidget, DbService::getInstance()->getCurrentDatabase());
    configureTableModel(tableModel, tableName, columnNames);

    for (auto relation : relations)
    {
        tableModel->setRelation(relation.first, relation.second);
    }


}

QTableView *EkonTabWidget::createTableView(QWidget* parentWidget, QSqlTableModel* model)
{
    QTableView *tableView = new QTableView(parentWidget);
    tableView->setModel(model);
    tableView->hideColumn(0);
    tableView->show();

    tableView->setStyleSheet("QHeaderView::section {background-color:grey}");
    tableView->verticalHeader()->hide();

    return tableView;
}
