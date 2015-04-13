#include "admin_widget.h"

AdminWidget::AdminWidget(QWidget *parent) :
    QTabWidget(parent)
{
    addUsersTab();
}

void AdminWidget::addUsersTab()
{
    QWidget *widget = new QWidget();
    _usersTableModel = new QSqlRelationalTableModel(widget, DbService::getInstance()->getCurrentDatabase());
    _usersTableModel->setTable("DRT_USERS");
    _usersTableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    _usersTableModel->setRelation(3, QSqlRelation("DRT_USER_TYPES", "UST_ID", "UST_NAME"));
    _usersTableModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    _usersTableModel->setHeaderData(1, Qt::Horizontal, tr("Логин"));
    _usersTableModel->setHeaderData(2, Qt::Horizontal, tr("Пароль"));
    _usersTableModel->setHeaderData(3, Qt::Horizontal, tr("Тип"));
    _usersTableModel->select();

    _usersTableView = new QTableView(widget);
    _usersTableView->setModel(_usersTableModel);
    _usersTableView->hideColumn(0);
    _usersTableView->setItemDelegate(new QSqlRelationalDelegate(_usersTableView));
    _usersTableView->show();

    _usersTableView->setStyleSheet("QHeaderView::section { background-color:grey }");
    _usersTableView->verticalHeader()->hide();

    QGridLayout *usersLayout = new QGridLayout(widget);
    usersLayout->addWidget(_usersTableView);

    this->addTab(widget, QString("Users"));
}
