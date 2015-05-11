#ifndef ADD_LOADCALCULATION_DIALOG_H
#define ADD_LOADCALCULATION_DIALOG_H

#include <database/db_service.h>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QDebug>

class AddLoadcalculationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddLoadcalculationDialog(QWidget *parent = 0);
    
private slots:
    void addRow();
    void setHours();

private:
    void createLayout();

private:
    QComboBox *flowComboBox;
    QComboBox *disciplineComboBox;
    QLabel *lecturesLabel;
    QLabel *laboratoryLabel;
    QLabel *practicalLabel;
    QLabel *consultationLabel;
    QLabel *examinationsLabel;
    QLabel *testsLabel;
    QLabel *currentConsultationLabel;
    QLabel *introductoryPracticeLabel;
    QLabel *preDiplomaPracticeLabel;
    QLabel *courseworkLabel;
    QLabel *guidedIndependentWorkLabel;
    QLabel *controlWorkLabel;
    QLabel *graduationDesignLabel;
    QLabel *guideGraduateLabel;
    QLabel *stateExamLabel;
    QLabel *hesLabel;
    QLabel *guideChairLabel;
    QLabel *uirsLabel;

    QPushButton *addButton;

    QList<Flow> flows;
    QList<Discipline> disciplines;
};

#endif // ADD_LOADCALCULATION_DIALOG_H
