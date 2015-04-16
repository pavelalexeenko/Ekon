#include "secretary_widget.h"

SecretaryWidget::SecretaryWidget(QWidget *parent) :
    EkonTabWidget(parent)
{
    addUsersTab();
    addDisciplinesTab();
    addTeachersTab();
}

void SecretaryWidget::search(QString str)
{

}

void SecretaryWidget::refresh()
{
    qDebug() << "SecretaryWidget::refresh()";
    usersTableModel->select();
    disciplinesTableModel->select();
    teachersTableModel->select();
}

void SecretaryWidget::addUsersTab()
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

    usersTableView = new QTableView(widget);
    usersTableView->setModel(usersTableModel);
    usersTableView->hideColumn(0);
    usersTableView->setItemDelegate(new QSqlRelationalDelegate(usersTableView));
    usersTableView->show();

    usersTableView->setStyleSheet("QHeaderView::section {background-color:grey}");
    usersTableView->verticalHeader()->hide();

    QGridLayout *usersLayout = new QGridLayout(widget);
    usersLayout->addWidget(usersTableView);

    this->addTab(widget, QString("Users"));
}

void SecretaryWidget::addDisciplinesTab()
{
    QStringList columnNames;
    columnNames << "ID"
                << "Название дисциплины"
                << "Лекции"
                << "Практики";

    QWidget *widget = new QWidget();
    disciplinesTableModel = new QSqlTableModel(widget, DbService::getInstance()->getCurrentDatabase());
    disciplinesTableModel = createTableModel("DRT_DISCIPLINES", columnNames);
    disciplinesTableView = createTableView(widget, disciplinesTableModel);

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(disciplinesTableView);

    this->addTab(widget, QString("Дисциплины"));
}

void SecretaryWidget::addTeachersTab()
{
    QStringList columnNames;
    columnNames << "ID"
                << "ФИО"
                << "Ставка"
                << "Примечание";

    QWidget *widget = new QWidget();
    teachersTableModel = new QSqlTableModel(widget, DbService::getInstance()->getCurrentDatabase());
    teachersTableModel = createTableModel("DRT_TEACHERS", columnNames);
    teachersTableView = createTableView(widget, teachersTableModel);

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(teachersTableView);

    this->addTab(widget, QString("Преподаватели"));
}

