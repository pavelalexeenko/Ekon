#ifndef CONTROL_WIDGET_H
#define CONTROL_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QDebug>

class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = 0);

signals:
    void search(QString);
    void filter(QString);
    void addRow();
    void removeRow();

private slots:
    void search();
    void filter();
    void setSearchType();

private:
    enum SearchType
    {
        SEARCH,
        FILTER
    };
    SearchType searchType;

    QPushButton *addRowButton;
    QPushButton *deleteRowButton;

    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QPushButton *filterButton;
};

#endif // CONTROL_WIDGET_H
