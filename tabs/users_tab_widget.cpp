#include "users_tab_widget.h"
#include <dialogs/add_user_dialog.h>

UsersTabWidget::UsersTabWidget(QWidget *parent) :
    QWidget(parent)
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
    layout->addWidget(controlWidget);

    this->setLayout(layout);
}

void UsersTabWidget::addRow()
{
    qDebug() << __FUNCTION__;
    AddUserDialog *aud = new AddUserDialog(this);
    connect(aud, SIGNAL(accepted()), this, SLOT(refresh()));
    aud->show();
}

void UsersTabWidget::refresh()
{
    qDebug() << __FUNCTION__;
    usersTableModel->select();
}
