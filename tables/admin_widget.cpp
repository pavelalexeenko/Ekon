#include "admin_widget.h"

AdminWidget::AdminWidget(QWidget *parent) :
    QTabWidget(parent)
{
    qDebug() << __FUNCTION__;

    usersWidget = new UsersWidget(this);
    this->addTab(usersWidget, QString("&Пользователи"));
    this->setStyleSheet("QTabWidget::pane { border: 0; }");
}

void AdminWidget::refresh()
{
    qDebug() << __FUNCTION__;

    usersWidget->refresh();
}
