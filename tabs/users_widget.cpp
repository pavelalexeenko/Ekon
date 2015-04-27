#include "users_widget.h"
#include "dialogs/add_user_dialog.h"

UsersWidget::UsersWidget(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << __FUNCTION__;

    QStringList columnNames;
    columnNames << "ID"
                << "Логин"
                << "Пароль"
                << "Тип";

    QList<QPair<int, QSqlRelation> > relations;
    relations.append(qMakePair(3, QSqlRelation("DRT_USER_TYPES", "UST_ID", "UST_NAME")));

    usersTableModel = EkonTables::createRelationalTableModel(this, "DRT_USERS", columnNames, relations);
    usersTableView = EkonTables::createRelationTableView(this, usersTableModel);

    controlWidget = new ControlWidget(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(usersTableView);
    layout->addWidget(controlWidget);

    this->setLayout(layout);

    connect(controlWidget, SIGNAL(addRow()), this, SLOT(addRow()));
}

void UsersWidget::addRow()
{
    qDebug() << __FUNCTION__;
    AddUserDialog *aud = new AddUserDialog(this);
    connect(aud, SIGNAL(accepted()), this, SLOT(refresh()));
    aud->show();
}

void UsersWidget::refresh()
{
    qDebug() << __FUNCTION__;
    usersTableModel->select();
}
