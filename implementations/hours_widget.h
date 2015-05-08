#ifndef HOURSWIDGET_H
#define HOURSWIDGET_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QGridLayout>

class HoursWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HoursWidget(QWidget *parent = 0);
    explicit HoursWidget(const double leftHours, const double totalHours, QWidget *parent = 0);

    void setHours(const double left, const double total);
    void setLeftHours(const double left);
    void setTotalHours(const double total);

    double getHours();

private:
    void initControlDefaults();
    void createLayout();

private:
    QDoubleSpinBox *hoursSpinBox;
    QLabel *leftHoursLabel;
    QLabel *totalHoursLabel;

    double _leftHours;
    double _totalHours;
};

#endif // HOURSWIDGET_H