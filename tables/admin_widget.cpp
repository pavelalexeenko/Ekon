#include "admin_widget.h"

AdminWidget::AdminWidget(QWidget *parent) :
    QTabWidget(parent)
{
    addUsersTab();
}

void AdminWidget::search(QString str)
{
    qDebug() << "AdminWidget::search(QString \"" + str + "\")";
    usersSortFilterProxyModel->setFilterRegExp(QRegExp(str, Qt::CaseInsensitive, QRegExp::FixedString));
}

void AdminWidget::addUsersTab()
{
    QWidget *widget = new QWidget();
    usersTableModel = new QSqlRelationalTableModel(widget, DbService::getInstance()->getCurrentDatabase());
    usersTableModel->setTable("DRT_USERS");
    usersTableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    usersTableModel->setRelation(3, QSqlRelation("DRT_USER_TYPES", "UST_ID", "UST_NAME"));
    usersTableModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    usersTableModel->setHeaderData(1, Qt::Horizontal, tr("Логин"));
    usersTableModel->setHeaderData(2, Qt::Horizontal, tr("Пароль"));
    usersTableModel->setHeaderData(3, Qt::Horizontal, tr("Тип"));
    usersTableModel->select();

    usersSortFilterProxyModel = new QSortFilterProxyModel(this);
    usersSortFilterProxyModel->setSourceModel(usersTableModel);

    usersTableView = new QTableView(widget);
    usersTableView->setModel(usersSortFilterProxyModel);
    usersTableView->hideColumn(0);
    usersTableView->setItemDelegate(new QSqlRelationalDelegate(usersTableView));
    usersTableView->setSortingEnabled(true);
    usersTableView->show();

    usersTableView->setStyleSheet("QHeaderView::section { background-color:grey }");
    usersTableView->verticalHeader()->hide();

    QGridLayout *usersLayout = new QGridLayout(widget);
    usersLayout->addWidget(usersTableView);

    this->addTab(widget, QString("Users"));
}
