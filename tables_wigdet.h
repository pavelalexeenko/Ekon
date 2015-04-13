#ifndef TABLES_WIGDET_H
#define TABLES_WIGDET_H

#include <tables/admin_widget.h>
#include <tables/secretary_widget.h>
#include <tables/worker_widget.h>
#include <database/db_service.h>

#include <QWidget>
#include <QStackedLayout>
#include <QSharedPointer>

class TablesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TablesWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void updateLayout();

private:
    QStackedLayout *_stackedLayout;

    AdminWidget *adminWidget;
    SecretaryWidget *secretaryWidget;
    WorkerWidget *workerWidget;

};

#endif // TABLES_WIGDET_H
