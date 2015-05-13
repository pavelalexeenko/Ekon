#include "admin_widget.h"

AdminWidget::AdminWidget(QWidget *parent) :
    QTabWidget(parent)
  , usersWidget(new UsersWidget(this))
  , settingsWidget(new SettingsWidget(this))
{
    qDebug() << __FUNCTION__;

    addTab(usersWidget, QString("&Пользователи"));
    addTab(settingsWidget, QString("&Настройки"));

    setStyleSheet("QTabWidget::pane { border: 0; }");
}

void AdminWidget::refresh()
{
    qDebug() << __FUNCTION__;

    usersWidget->refresh();
}
