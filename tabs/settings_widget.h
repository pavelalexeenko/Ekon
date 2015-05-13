#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include "implementations/ekon_tables.h"

#include <QWidget>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QDataWidgetMapper>
#include <QGroupBox>
#include <QSizePolicy>

#include <QDebug>

class SettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWidget(QWidget *parent = 0);

private:
    void createLayout();
    void createMapper();

private:
    QDoubleSpinBox *consultationDoubleSpinBox;
    QDoubleSpinBox *examinationDoubleSpinBox;
    QDoubleSpinBox *testsDoubleSpinBox;
    QDoubleSpinBox *currentConsultationDoubleSpinBox;
    QDoubleSpinBox *introductoryPracticeDoubleSpinBox;
    QDoubleSpinBox *preDiplomaPracticeDoubleSpinBox;
    QDoubleSpinBox *courseWorkDoubleSpinBox;
    QDoubleSpinBox *guidedIndependentWorkDoubleSpinBox;
    QDoubleSpinBox *controlWorkDoubleSpinBox;
    QDoubleSpinBox *graduationDesignDoubleSpinBox;
    QDoubleSpinBox *guideGraduateDoubleSpinBox;
    QDoubleSpinBox *stateExamDoubleSpinBox;
    QDoubleSpinBox *hesDoubleSpinBox;
    QDoubleSpinBox *guideChairDoubleSpinBox;
    QDoubleSpinBox *uirsDoubleSpinBox;
};

#endif // SETTINGSWIDGET_H
