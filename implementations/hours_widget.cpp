#include "hours_widget.h"

HoursWidget::HoursWidget(QWidget *parent) :
    QWidget(parent)
  , hoursSpinBox(new QDoubleSpinBox(this))
  , leftHoursLabel(new QLabel(QString("Осталось: 0 "),this))
  , totalHoursLabel(new QLabel(QString("Всего: 0 "),this))
  , _leftHours(0)
  , _totalHours(0)
{
    initControlDefaults();
    createLayout();
}

HoursWidget::HoursWidget(const double leftHours, const double totalHours, QWidget *parent) :
    QWidget(parent)
  , hoursSpinBox(new QDoubleSpinBox(this))
  , leftHoursLabel(new QLabel(QString("Осталось: %1 ").arg(leftHours),this))
  , totalHoursLabel(new QLabel(QString("Всего: %1 ").arg(totalHours),this))
  , _leftHours(leftHours)
  , _totalHours(totalHours)
{
    initControlDefaults();
    createLayout();
}

void HoursWidget::setHours(const double left, const double total)
{
    setLeftHours(left);
    setTotalHours(total);
}

void HoursWidget::setLeftHours(const double left)
{
    _leftHours = left;
    hoursSpinBox->setMaximum(_leftHours);
    leftHoursLabel->setText(QString("Осталось: %1 ").arg(_leftHours));
    this->updateGeometry();
}

void HoursWidget::setTotalHours(const double total)
{
    _totalHours = total;
    totalHoursLabel->setText(QString("Всего: %1 ").arg(_totalHours));
    this->updateGeometry();
}

double HoursWidget::getHours()
{
    return hoursSpinBox->value();
}

void HoursWidget::initControlDefaults()
{
    hoursSpinBox->setMinimum(0);
    hoursSpinBox->setMaximum(_leftHours);
}

void HoursWidget::createLayout()
{
    leftHoursLabel->setSizePolicy(QSizePolicy::MinimumExpanding , QSizePolicy::Minimum);
    totalHoursLabel->setSizePolicy(QSizePolicy::MinimumExpanding , QSizePolicy::Minimum);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(hoursSpinBox, 2);
    layout->addWidget(leftHoursLabel, 1);
    layout->addWidget(totalHoursLabel, 1);
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(layout);
}
