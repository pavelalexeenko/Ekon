#include "add_discipline_dialog.h"

AddDisciplineDialog::AddDisciplineDialog(QWidget *parent):
    QDialog(parent)
{
    namePlainTextEdit = new QPlainTextEdit(this);
    lecturesSpinBox = new QDoubleSpinBox(this);
    laboratorySpinBox = new QDoubleSpinBox(this);
    practicalSpinBox = new QDoubleSpinBox(this);

    consultationCheckBox = new QCheckBox("&Консультации", this);
    examinationCheckBox = new QCheckBox("&Зачет", this);
    testsCheckBox = new QCheckBox("&TESTS", this);
    currentConsultationCheckBox = new QCheckBox("&Текущая консультация", this);
    introductoryPracticeCheckBox = new QCheckBox("&INTRODUCTORY PRACTICE", this);
    preDiplomaPracticeCheckBox = new QCheckBox("&Преддипломная практика", this);
    courseWorkCheckBox = new QCheckBox("Курсовая &работа", this);
    guidedIndependentWorkCheckBox = new QCheckBox("&GUIDED_INDEPENDENT_WORK", this);
    controlWorkCheckBox = new QCheckBox("К&онтрольная работа", this);
    graduationDesignCheckBox = new QCheckBox("&GRADUATION_DESIGN", this);
    guideGraduateCheckBox = new QCheckBox("&GUIDE_GRADUATE", this);
    stateExamCheckBox = new QCheckBox("&Экзамен", this);
    hesCheckBox = new QCheckBox("&ГЭК", this);
    guideChairCheckBox = new QCheckBox("&GUIDE_CHAIR", this);
    uirsCheckBox = new QCheckBox("&УИРС", this);

    addButton = new QPushButton(QString("Добавить"), this);

    namePlainTextEdit->setMinimumHeight(30);
    namePlainTextEdit->setMinimumWidth(200);

    lecturesSpinBox->setMinimum(0);
    lecturesSpinBox->setSingleStep(1);
    laboratorySpinBox->setMinimum(0);
    laboratorySpinBox->setSingleStep(1);
    practicalSpinBox->setMinimum(0);
    practicalSpinBox->setSingleStep(1);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));

    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow(tr("&Название дисциплины:"), namePlainTextEdit);
    formLayout->addRow(tr("&Лекции:"), lecturesSpinBox);
    formLayout->addRow(tr("&Лабораторные:"), laboratorySpinBox);
    formLayout->addRow(tr("&Практические:"), practicalSpinBox);
    formLayout->addRow(consultationCheckBox, examinationCheckBox);
    formLayout->addRow(testsCheckBox, currentConsultationCheckBox);
    formLayout->addRow(introductoryPracticeCheckBox, preDiplomaPracticeCheckBox);
    formLayout->addRow(courseWorkCheckBox, guidedIndependentWorkCheckBox);
    formLayout->addRow(controlWorkCheckBox, graduationDesignCheckBox);
    formLayout->addRow(guideGraduateCheckBox, stateExamCheckBox);
    formLayout->addRow(hesCheckBox, guideChairCheckBox);
    formLayout->addRow(uirsCheckBox);
    formLayout->addRow(tr(""), addButton);
    setLayout(formLayout);
}

void AddDisciplineDialog::addRow()
{
    qDebug() << __FUNCTION__;

    if (0)
    {
        QMessageBox::critical(this, tr("Error"), tr("Some fields are empty."), QMessageBox::Ok);
        return;
    }

    if (0)
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Database error while adding a discipline."), QMessageBox::Ok);

}
