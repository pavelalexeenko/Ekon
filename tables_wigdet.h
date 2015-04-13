#ifndef TABLES_WIGDET_H
#define TABLES_WIGDET_H

#include <tables/admin_widget.h>
#include <tables/worker_widget.h>

#include <QWidget>
#include <QStackedLayout>

class TablesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TablesWidget(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QStackedLayout *_stackedLayout;
};

#endif // TABLES_WIGDET_H
