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

private slots:
    void addRow();
    void setHours();

private:
    void createLayout();
    void fillComboBoxes();

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
    HoursWidget *controlHoursWidget;
    HoursWidget *graduationDesignHoursWidget;
    HoursWidget *guideGraduateHoursWidget;
    HoursWidget *stateExamHoursWidget;
    HoursWidget *hesHoursWidget;
    HoursWidget *guideChairHoursWidget;
    HoursWidget *uirsHoursWidget;

    QPushButton *addButton;
};

#endif // ADDLOADDISTRIBUTIONDIALOG_H
