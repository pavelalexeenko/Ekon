#include "add_discipline_dialog.h"

AddDisciplineDialog::AddDisciplineDialog(QWidget *parent):
    QDialog(parent)
  , namePlainTextEdit(new QPlainTextEdit(this))
  , lecturesSpinBox(new QDoubleSpinBox(this))
  , laboratorySpinBox(new QDoubleSpinBox(this))
  , practicalSpinBox(new QDoubleSpinBox(this))
  , consultationCheckBox(new QCheckBox("&Консультации", this))
  , examinationCheckBox(new QCheckBox("&Экзамен", this))
  , testsCheckBox(new QCheckBox("&Зачет", this))
  , currentConsultationCheckBox(new QCheckBox("&Текущая консультация", this))
  , introductoryPracticeCheckBox(new QCheckBox("&Ознакомительная практика", this))
  , preDiplomaPracticeCheckBox(new QCheckBox("&Преддипломная практика", this))
  , courseWorkCheckBox(new QCheckBox("Курсовая &работа", this))
  , guidedIndependentWorkCheckBox(new QCheckBox("&Управляемая самост. работа", this))
  , controlWorkCheckBox(new QCheckBox("К&онтрольная работа", this))
  , graduationDesignCheckBox(new QCheckBox("&Дипломное проектирование", this))
  , guideGraduateCheckBox(new QCheckBox("&Рук-во аспирантами", this))
  , stateExamCheckBox(new QCheckBox("&Гос экзамен", this))
  , hesCheckBox(new QCheckBox("&ГЭК", this))
  , guideChairCheckBox(new QCheckBox("&Руководство кафедрой", this))
  , uirsCheckBox(new QCheckBox("&УИРС", this))
  , addButton(new QPushButton(QString("Добавить"), this))
{
    qDebug() << __FUNCTION__;
    setWindowTitle("Добавление дисциплины");

    namePlainTextEdit->setMinimumHeight(30);
    namePlainTextEdit->setMinimumWidth(200);

    lecturesSpinBox->setMinimum(0);
    lecturesSpinBox->setSingleStep(1);
    lecturesSpinBox->setMaximum(10000);
    laboratorySpinBox->setMinimum(0);
    laboratorySpinBox->setSingleStep(1);
    laboratorySpinBox->setMaximum(10000);
    practicalSpinBox->setMinimum(0);
    practicalSpinBox->setSingleStep(1);
    practicalSpinBox->setMaximum(10000);

    createLayout();

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));
}

void AddDisciplineDialog::addRow()
{
    qDebug() << __FUNCTION__;

    if (namePlainTextEdit->toPlainText().isEmpty())
    {
        QMessageBox::critical(this, tr("Error"), tr("Some fields are empty."), QMessageBox::Ok);
        return;
    }

    Discipline discipline;
    discipline.setName(namePlainTextEdit->toPlainText());
    discipline.setLectures(lecturesSpinBox->value());
    discipline.setLaboratory(laboratorySpinBox->value());
    discipline.setPractical(practicalSpinBox->value());
    discipline.setConsultation(consultationCheckBox->isChecked());
    discipline.setExaminations(examinationCheckBox->isChecked());
    discipline.setTests(testsCheckBox->isChecked());
    discipline.setCurrentConsultation(currentConsultationCheckBox->isChecked());
    discipline.setIntroductoryPractice(introductoryPracticeCheckBox->isChecked());
    discipline.setPreDiplomaPractice(preDiplomaPracticeCheckBox->isChecked());
    discipline.setCourseWork(courseWorkCheckBox->isChecked());
    discipline.setGuidedIndependentWork(guidedIndependentWorkCheckBox->isChecked());
    discipline.setControlWork(controlWorkCheckBox->isChecked());
    discipline.setGraduationDesign(graduationDesignCheckBox->isChecked());
    discipline.setGuideGraduate(guideGraduateCheckBox->isChecked());
    discipline.setStateExam(stateExamCheckBox->isChecked());
    discipline.setHes(hesCheckBox->isChecked());
    discipline.setGuideChair(guideChairCheckBox->isChecked());
    discipline.setUirs(uirsCheckBox->isChecked());

    if (DbService::getInstance()->addDiscipline(discipline))
        this->accept();
    else
        QMessageBox::critical(this, tr("Ошибка"), tr("Такая дисциплина уже существует."), QMessageBox::Ok);

}

void AddDisciplineDialog::createLayout()
{
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
