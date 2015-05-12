#ifndef LOADDISTRIBUTIONDIALOG_H
#define LOADDISTRIBUTIONDIALOG_H

#include <database/db_service.h>
#include <implementations/hours_widget.h>

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QFormLayout>

class LoadDistributionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoadDistributionDialog(QWidget *parent = 0);

protected slots:
    virtual void saveRow() = 0;
    virtual void updateView() = 0;
    void setHours(LoadCalculation notDistributedLcl, LoadCalculation totalLcl, LoadDistribution currentLoadDistribution);

protected:
    void setConnections();
    void createLayout();
    void fillLclCombo();

    LoadDistribution getLoadDistribution();

protected:
    QComboBox *loadcalculationComboBox;
    QComboBox *teacherComboBox;

    HoursWidget *lecturesHoursWidget;
    HoursWidget *laboratoryHoursWidget;
    HoursWidget *practicalHoursWidget;
    HoursWidget *consultationHoursWidget;
    HoursWidget *examinationsHoursWidget;
    HoursWidget *testsHoursWidget;
    HoursWidget *currentConsultationHoursWidget;
    HoursWidget *introductoryPracticeHoursWidget;
    HoursWidget *preDiplomaPracticeHoursWidget;
    HoursWidget *courseworkHoursWidget;
    HoursWidget *guidedIndependentWorkHoursWidget;
    HoursWidget *controlWorkHoursWidget;
    HoursWidget *graduationDesignHoursWidget;
    HoursWidget *guideGraduateHoursWidget;
    HoursWidget *stateExamHoursWidget;
    HoursWidget *hesHoursWidget;
    HoursWidget *guideChairHoursWidget;
    HoursWidget *uirsHoursWidget;

    QPushButton *addButton;
};

#endif // LOADDISTRIBUTIONDIALOG_H
