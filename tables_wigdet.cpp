#include "tables_wigdet.h"

TablesWidget::TablesWidget(QWidget *parent) :
    QWidget(parent)
{
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

void TablesWidget::search(QString str)
{
    qDebug() << "TablesWidget::search(QString \"" + str + "\")";
    switch (stackedLayout->currentIndex()) {
    case Tab::ADMINISTRATOR_TAB:
        adminWidget->search(str);
        break;
    case Tab::SECRETARY_TAB:
        secretaryWidget->search(str);
        break;
    case Tab::WORKER_TAB:
        workerWidget->search(str);
        break;
    }
}

void TablesWidget::refresh()
{
    adminWidget->refresh();
    secretaryWidget->refresh();
    workerWidget->refresh();
}

void TablesWidget::updateLayout()
{
    qDebug() << "Updating stacked layout...";
    switch (DbService::getInstance()->getCurrentUser()->getUserRole()) {
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

void TablesWidget::addRow()
{

}
