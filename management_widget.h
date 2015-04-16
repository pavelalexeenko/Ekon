#ifndef MANAGEMENTWIDGET_H
#define MANAGEMENTWIDGET_H

#include <tables_wigdet.h>

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCompleter>
#include <QGridLayout>

class ManagementWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ManagementWidget(QWidget *parent = 0);

signals:

public slots:
    void updateLayout();
    void refresh();

private slots:
    void search();


private:
    TablesWidget *tablesWidget;

    QPushButton *addRowButton;
    QPushButton *deleteRowButton;

    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
};

#endif // MANAGEMENTWIDGET_H
