#include "ekon_tab_widget.h"
#include "implementations/mydelegate.h"

EkonTabWidget::EkonTabWidget(QWidget *parent) : QTabWidget(parent)
{

}

void EkonTabWidget::configureTableModel(QSqlTableModel *tableModel, QStringList columnNames)
{
    tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    for (int i = 0; i < columnNames.length(); i++)
    {
        tableModel->setHeaderData(i, Qt::Horizontal, columnNames.at(i));
    }

    tableModel->select();

    qDebug() << tableModel->tableName() << " - " << tableModel->lastError();
}

void EkonTabWidget::configureTableView(QTableView *tableView)
{

}

QSqlTableModel* EkonTabWidget::createTableModel(QWidget *parentWidget, QString tableName, QStringList columnNames)
{ 
    QSqlTableModel *tableModel = new QSqlTableModel(parentWidget, DbService::getInstance()->getCurrentDatabase());
    tableModel->setTable(tableName);
    configureTableModel(tableModel, columnNames);
    return tableModel;
}

QSqlRelationalTableModel* EkonTabWidget::createRelationalTableModel(QWidget *parentWidget, QString tableName, QStringList columnNames, QList<QPair<int, QSqlRelation> > relations)
{
    QSqlRelationalTableModel *tableModel = new QSqlRelationalTableModel(parentWidget, DbService::getInstance()->getCurrentDatabase());
    tableModel->setTable(tableName);

    for (auto relation : relations)
        tableModel->setRelation(relation.first, relation.second);

    configureTableModel(tableModel, columnNames);

    return tableModel;
}

QTableView* EkonTabWidget::createTableView(QWidget* parentWidget, QSqlTableModel* model)
{
    QTableView *tableView = new QTableView(parentWidget);
    tableView->setModel(model);
    tableView->hideColumn(0);
    tableView->show();
    tableView->setSortingEnabled(true);
    tableView->setDragEnabled(true);
   // tableView->setStyleSheet("QHeaderView::section {background-color:grey}");
    tableView->verticalHeader()->hide();
    tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    for (auto i = 2; i < model->columnCount(); i++)
        tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);

    return tableView;
}

QTableView* EkonTabWidget::createRelationTableView(QWidget *parentWidget, QSqlRelationalTableModel *model)
{
    QTableView *tableView = createTableView(parentWidget, model);
    tableView->setItemDelegate(new QSqlRelationalDelegate(tableView));

    return tableView;
}
