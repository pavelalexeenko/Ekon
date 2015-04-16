#include "ekon_tab_widget.h"

EkonTabWidget::EkonTabWidget(QWidget *parent) : QTabWidget(parent)
{

}

void EkonTabWidget::configureTableModel(QSqlTableModel *tableModel, QString tableName, QStringList columnNames)
{
    tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    for (int i = 0; i < columnNames.length(); i++)
    {
        tableModel->setHeaderData(i, Qt::Horizontal, columnNames.at(i));
    }

    tableModel->select();
}

void EkonTabWidget::configureTableView(FreezeTableWidget *tableView)
{

}

QSqlTableModel* EkonTabWidget::createTableModel(QWidget *parentWidget, QString tableName, QStringList columnNames)
{ 
    QSqlTableModel *tableModel = new QSqlTableModel(parentWidget, DbService::getInstance()->getCurrentDatabase());
    tableModel->setTable(tableName);
    configureTableModel(tableModel, tableName, columnNames);
    return tableModel;
}

QSqlRelationalTableModel* EkonTabWidget::createRelationalTableModel(QWidget *parentWidget, QString tableName, QStringList columnNames, QList<QPair<int, QSqlRelation> > relations)
{
    QSqlRelationalTableModel *tableModel = new QSqlRelationalTableModel(parentWidget, DbService::getInstance()->getCurrentDatabase());    
    tableModel->setTable(tableName);

    for (auto relation : relations)
        tableModel->setRelation(relation.first, relation.second);

    configureTableModel(tableModel, tableName, columnNames);

    return tableModel;
}

FreezeTableWidget* EkonTabWidget::createTableView(QWidget* parentWidget, QSqlTableModel* model)
{
    FreezeTableWidget *tableView = new FreezeTableWidget(model, parentWidget);
    tableView->hideColumn(0);
    tableView->show();
    tableView->setSortingEnabled(true);
    tableView->setStyleSheet("QHeaderView::section {background-color:grey}");
    tableView->verticalHeader()->hide();
    tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    for (auto i = 2; i < model->columnCount(); i++)
        tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);

    return tableView;
}

FreezeTableWidget* EkonTabWidget::createRelationTableView(QWidget *parentWidget, QSqlRelationalTableModel *model)
{
    FreezeTableWidget *tableView = createTableView(parentWidget, model);
    tableView->setItemDelegate(new QSqlRelationalDelegate(tableView));

    return tableView;
}
