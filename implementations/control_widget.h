#ifndef CONTROL_WIDGET_H
#define CONTROL_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCompleter>
#include <QGridLayout>

class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = 0);

signals:
    void search(QString);
    void addRow();
    void removeRow();

private slots:
    void search();

private:
    QPushButton *addRowButton;
    QPushButton *deleteRowButton;

    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
};

#endif // CONTROL_WIDGET_H
