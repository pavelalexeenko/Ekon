#ifndef TABLES_WIGDET_H
#define TABLES_WIGDET_H

#include <tables/admin_widget.h>
#include <tables/manager_widget.h>
#include <tables/secretary_widget.h>
#include <database/db_service.h>

#include <QWidget>
#include <QStackedLayout>
#include <QSharedPointer>

class TablesWidget : public QWidget
{
    enum Tab
    {
        ADMINISTRATOR_TAB = 1,
        SECRETARY_TAB = 2,
        WORKER_TAB = 3
    };

    Q_OBJECT
public:
    explicit TablesWidget(QWidget *parent = 0);

signals:
    
public slots:
    void updateLayout();
    void refresh();

private:
    QStackedLayout *stackedLayout;

    AdminWidget *adminWidget;
    ManagerWidget *managerWidget;
    SecretaryWidget *secretaryWidget;

};

#endif // TABLES_WIGDET_H
