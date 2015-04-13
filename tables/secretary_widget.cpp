#include "secretary_widget.h"

SecretaryWidget::SecretaryWidget(QWidget *parent) :
    QTabWidget(parent)
{
    addUsersTab();
    addDisciplinesTab();
    addTeachersTab();
}

void SecretaryWidget::addUsersTab()
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

void SecretaryWidget::addDisciplinesTab()
{
    QWidget *widget = new QWidget();
    _disciplinesTableModel = new QSqlRelationalTableModel(widget, DbService::getInstance()->getCurrentDatabase());
    _disciplinesTableModel->setTable("DRT_DISCIPLINES");
    _disciplinesTableModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    _disciplinesTableModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    _disciplinesTableModel->setHeaderData(1, Qt::Horizontal, tr("Название дисциплины"));
    _disciplinesTableModel->setHeaderData(2, Qt::Horizontal, tr("Лекции"));
    _disciplinesTableModel->setHeaderData(3, Qt::Horizontal, tr("Практики"));
    _disciplinesTableModel->select();

    _disciplinesTableView = new QTableView(widget);
    _disciplinesTableView->setModel(_disciplinesTableModel);
    _disciplinesTableView->hideColumn(0);
    _disciplinesTableView->show();

    _disciplinesTableView->setStyleSheet("QHeaderView::section { background-color:grey }");
    _disciplinesTableView->verticalHeader()->hide();

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(_disciplinesTableView);

    this->addTab(widget, QString("Дисциплины"));
}

void SecretaryWidget::addTeachersTab()
{
    QWidget *widget = new QWidget();
    _teachersTableModel = new QSqlRelationalTableModel(widget, DbService::getInstance()->getCurrentDatabase());
    _teachersTableModel->setTable("DRT_TEACHERS");
    _teachersTableModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    _teachersTableModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    _teachersTableModel->setHeaderData(1, Qt::Horizontal, tr("ФИО"));
    _teachersTableModel->setHeaderData(2, Qt::Horizontal, tr("Ставка"));
    _teachersTableModel->setHeaderData(3, Qt::Horizontal, tr("Примечание"));
    _teachersTableModel->select();

    _teachersTableView = new QTableView(widget);
    _teachersTableView->setModel(_teachersTableModel);
    _teachersTableView->hideColumn(0);
    _teachersTableView->show();

    _teachersTableView->setStyleSheet("QHeaderView::section { background-color:grey }");
    _teachersTableView->verticalHeader()->hide();

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(_teachersTableView);

    this->addTab(widget, QString("Преподаватели"));
}
