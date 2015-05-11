#ifndef ADDLOADDISTRIBUTIONDIALOG_H
#define ADDLOADDISTRIBUTIONDIALOG_H

#include <database/db_service.h>
#include <implementations/hours_widget.h>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>

class AddLoadDistributionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddLoadDistributionDialog(QWidget *parent = 0);
    explicit AddLoadDistributionDialog(const int loadDistributionId, QWidget *parent = 0);

private slots:
    void saveRow();
    void setHours();
    void checkTeacher(bool firstShow = false);
    void fillComboBoxes();

private:
    void createLayout();   
    void setConnections();
    void setEmptyHours(LoadCalculation notDistributedLcl, LoadCalculation totalLcl, LoadDistribution currentLoadDistribution);

private:
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

    int _id;
    QList<int> teachersThatAlreadyStudyWithLcl;
};

#endif // ADDLOADDISTRIBUTIONDIALOG_H
