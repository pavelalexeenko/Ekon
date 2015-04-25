#ifndef ADDDISCIPLINEDIALOG_H
#define ADDDISCIPLINEDIALOG_H

#include <database/db_service.h>

#include <QWidget>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>
#include <QDebug>

class AddDisciplineDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddDisciplineDialog(QWidget *parent = 0);

private slots:
    void addRow();

private:
    QPlainTextEdit *namePlainTextEdit;
    QDoubleSpinBox *lecturesSpinBox;
    QDoubleSpinBox *laboratorySpinBox;
    QDoubleSpinBox *practicalSpinBox;
    QCheckBox *consultationCheckBox;
    QCheckBox *examinationCheckBox;
    QCheckBox *testsCheckBox;
    QCheckBox *currentConsultationCheckBox;
    QCheckBox *introductoryPracticeCheckBox;
    QCheckBox *preDiplomaPracticeCheckBox;
    QCheckBox *courseWorkCheckBox;
    QCheckBox *guidedIndependentWorkCheckBox;
    QCheckBox *controlWorkCheckBox;
    QCheckBox *graduationDesignCheckBox;
    QCheckBox *guideGraduateCheckBox;
    QCheckBox *stateExamCheckBox;
    QCheckBox *hesCheckBox;
    QCheckBox *guideChairCheckBox;
    QCheckBox *uirsCheckBox;

    QPushButton *addButton;
};

#endif // ADDDISCIPLINEDIALOG_H
