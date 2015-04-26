#include "admin_widget.h"
#include <dialogs/add_user_dialog.h>

AdminWidget::AdminWidget(QWidget *parent) :
    QTabWidget(parent)
{
    UsersTabWidget *usersWidget = new UsersTabWidget();

    this->addTab(usersWidget, QString("Пользователи"));
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

void AdminWidget::addRow()
{
    qDebug() << "AdminWidget::addRow()";
    AddUserDialog *aud = new AddUserDialog(this);
    connect(aud, SIGNAL(accepted()), this, SLOT(refresh()));
    aud->show();
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
    usersTableModel = EkonTables::createRelationalTableModel(widget, "DRT_USERS", columnNames, relations);
    usersTableView = EkonTables::createRelationTableView(widget, usersTableModel);

    QGridLayout *layout = new QGridLayout(widget);
    layout->addWidget(usersTableView);

    this->addTab(widget, QString("Пользователи"));
}
