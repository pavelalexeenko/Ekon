#ifndef ADMIN_WIDGET_H
#define ADMIN_WIDGET_H

#include <QTabWidget>
#include "tabs/users_widget.h"
#include "tabs/settings_widget.h"

class AdminWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit AdminWidget(QWidget *parent = 0);

public slots:
    void refresh();

private:
    UsersWidget *usersWidget;
    SettingsWidget *settingsWidget;
};

#endif // ADMIN_WIDGET_H
