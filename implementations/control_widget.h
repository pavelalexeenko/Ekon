#ifndef CONTROL_WIDGET_H
#define CONTROL_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QDebug>

#include <QCompleter>
#include <QDirModel>

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
    void addWord(QString str);

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

    QStringList wordList;
};

#endif // CONTROL_WIDGET_H
