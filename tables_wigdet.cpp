#include "tables_wigdet.h"

TablesWidget::TablesWidget(QWidget *parent) :
    QWidget(parent)
{
    adminWidget = new AdminWidget(this);
    secretaryWidget = new SecretaryWidget(this);
    workerWidget = new WorkerWidget(this);

    _stackedLayout = new QStackedLayout(this);
    _stackedLayout->addWidget(adminWidget);
    _stackedLayout->addWidget(secretaryWidget);
    _stackedLayout->addWidget(workerWidget);

    this->setLayout(_stackedLayout);

}

void TablesWidget::updateLayout()
{
    qDebug() << "Updating stacked layout...";
    switch (DbService::getInstance()->getCurrentUser()->getUserRole()) {
    case User::ADMINISTRATOR:
        _stackedLayout->setCurrentIndex(0);
        break;
    case User::SECRETARY:
        _stackedLayout->setCurrentIndex(1);
        break;
    case User::WORKER:
        _stackedLayout->setCurrentIndex(2);
        break;
    case User::USER_ROLE_UNDEFINED:
        _stackedLayout->setCurrentIndex(3);
        break;
    default:
        _stackedLayout->setCurrentIndex(3);
        break;
    }
}
