#include "tables_wigdet.h"

TablesWidget::TablesWidget(QWidget *parent) :
    QWidget(parent)
{

    AdminWidget *adminWidget = new AdminWidget(this);
    WorkerWidget *workerWidget = new WorkerWidget(this);

    _stackedLayout = new QStackedLayout(this);
    _stackedLayout->addWidget(adminWidget);
    _stackedLayout->addWidget(workerWidget);

    this->setLayout(_stackedLayout);
}
