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
    explicit HoursWidget(const QString& labelText, QWidget *parent = 0);

    void setHours(const double left, const double total, const double active = 0);
    void setLeftHours(const double left);
    void setTotalHours(const double total);
    void setActiveHours(const double active);

    double getHours();

private:
    void initControlDefaults();
    void createLayout();

private:
    QLabel *nameLabel;
    QDoubleSpinBox *hoursSpinBox;
    QLabel *leftHoursLabel;
    QLabel *totalHoursLabel;

    double _activeHours;
    double _leftHours;
    double _totalHours;
};

#endif // HOURSWIDGET_H
