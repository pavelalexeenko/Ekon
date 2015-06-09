#include "tables_wigdet.h"

TablesWidget::TablesWidget(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << __FUNCTION__;
    adminWidget = new AdminWidget(this);
    managerWidget = new ManagerWidget(this);
    secretaryWidget = new SecretaryWidget(this);

    stackedLayout = new QStackedLayout(this);
    stackedLayout->addWidget(new QWidget(this));
    stackedLayout->addWidget(adminWidget);
    stackedLayout->addWidget(managerWidget);
    stackedLayout->addWidget(secretaryWidget);

    this->setLayout(stackedLayout);
}

void TablesWidget::refresh()
{
    qDebug() << __FUNCTION__;
    switch (DbService::getInstance()->getCurrentUser()->getUserrole()) {
    case User::ADMINISTRATOR:
        adminWidget->refresh();
        break;
    case User::MANAGER:
        managerWidget->refresh();
        break;
    case User::SECRETARY:
        secretaryWidget->refresh();
        break;
    default:
        break;
    }
}

void TablesWidget::updateLayout()
{
    qDebug() << __FUNCTION__;
    switch (DbService::getInstance()->getCurrentUser()->getUserrole()) {
    case User::ADMINISTRATOR:
        stackedLayout->setCurrentIndex(Tab::ADMINISTRATOR_TAB);
        break;
    case User::MANAGER:
        stackedLayout->setCurrentIndex(Tab::MANAGER_TAB);
        break;
    case User::SECRETARY:
        stackedLayout->setCurrentIndex(Tab::SECRETARY_TAB);
        break;
    default:
        stackedLayout->setCurrentIndex(0);
        break;
    }
}
