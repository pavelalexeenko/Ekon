#include "tables_wigdet.h"

TablesWidget::TablesWidget(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << __FUNCTION__;
    adminWidget = new AdminWidget(this);
    secretaryWidget = new SecretaryWidget(this);
    workerWidget = new WorkerWidget(this);

    stackedLayout = new QStackedLayout(this);
    stackedLayout->addWidget(new QWidget(this));
    stackedLayout->addWidget(adminWidget);
    stackedLayout->addWidget(secretaryWidget);
    stackedLayout->addWidget(workerWidget);

    this->setLayout(stackedLayout);
}

void TablesWidget::refresh()
{
    qDebug() << __FUNCTION__;
    switch (DbService::getInstance()->getCurrentUser()->getUserrole()) {
    case User::ADMINISTRATOR:
        adminWidget->refresh();
        break;
    case User::SECRETARY:
        secretaryWidget->refresh();
        break;
    case User::WORKER:
        workerWidget->refresh();
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
    case User::SECRETARY:
        stackedLayout->setCurrentIndex(Tab::SECRETARY_TAB);
        break;
    case User::WORKER:
        stackedLayout->setCurrentIndex(Tab::WORKER_TAB);
        break;
    default:
        stackedLayout->setCurrentIndex(0);
        break;
    }
}
