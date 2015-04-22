#include "admin_widget.h"

AdminWidget::AdminWidget(QWidget *parent) :
    EkonTabWidget(parent)
{
    addUsersTab();
}

void AdminWidget::search(QString str)
{
    qDebug() << "AdminWidget::search(QString \"" + str + "\")";
    // usersSortFilterProxyModel->setFilterRegExp(QRegExp(str, Qt::CaseInsensitive, QRegExp::FixedString));
}

void AdminWidget::refresh()
{
    qDebug() << "AdminWidget::refresh()";
    usersTableModel->select();
}

void AdminWidget::addUsersTab()
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
