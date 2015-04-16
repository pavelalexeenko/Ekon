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
    qDebug() << "SecretaryWidget::search(QString \"" + str + "\")";
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
    QStringList columnNames;
    columnNames << "ID"
                << "Логин"
                << "Пароль"
                << "Тип";

    QList<QPair<int, QSqlRelation> > relations;
    relations.append(qMakePair(3, QSqlRelation("DRT_USER_TYPES", "UST_ID", "UST_NAME")));

    QWidget *widget = new QWidget();
    usersTableModel = createRelationalTableModel(widget, "DRT_USERS", columnNames, relations);
    usersTableView = createRelationTableView(widget, usersTableModel);

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(usersTableView);

    this->addTab(widget, QString("Пользователи"));
}

void SecretaryWidget::addDisciplinesTab()
{
    QStringList columnNames;
    columnNames << "ID"
                << "Название дисциплины"
                << "Лекции"
                << "Практики";

    QWidget *widget = new QWidget();
    disciplinesTableModel = createTableModel(widget, "DRT_DISCIPLINES", columnNames);
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
    teachersTableModel = createTableModel(widget, "DRT_TEACHERS", columnNames);
    teachersTableView = createTableView(widget, teachersTableModel);

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(teachersTableView);

    this->addTab(widget, QString("Преподаватели"));
}

