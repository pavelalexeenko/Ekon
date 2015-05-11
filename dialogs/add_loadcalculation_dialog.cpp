#include "add_loadcalculation_dialog.h"

AddLoadcalculationDialog::AddLoadcalculationDialog(QWidget *parent) :
    QDialog(parent)
  , flowComboBox(new QComboBox(this))
  , disciplineComboBox(new QComboBox(this))
  , lecturesLabel(new QLabel(this))
  , laboratoryLabel(new QLabel(this))
  , practicalLabel(new QLabel(this))
  , consultationLabel(new QLabel(this))
  , examinationsLabel(new QLabel(this))
  , testsLabel(new QLabel(this))
  , currentConsultationLabel(new QLabel(this))
  , introductoryPracticeLabel(new QLabel(this))
  , preDiplomaPracticeLabel(new QLabel(this))
  , courseworkLabel(new QLabel(this))
  , guidedIndependentWorkLabel(new QLabel(this))
  , controlWorkLabel(new QLabel(this))
  , graduationDesignLabel(new QLabel(this))
  , guideGraduateLabel(new QLabel(this))
  , stateExamLabel(new QLabel(this))
  , hesLabel(new QLabel(this))
  , guideChairLabel(new QLabel(this))
  , uirsLabel(new QLabel(this))
  , addButton(new QPushButton("Добавить", this))
{
    qDebug() << __FUNCTION__;
    setWindowTitle("Добавление расчета нагрузки");

    flows = DbService::getInstance()->getAllFlows();
    disciplines = DbService::getInstance()->getAllDisciplines();

    for (Flow &flow : flows)
        flowComboBox->addItem(flow.getName(), QVariant(flow.getId()));

    for (Discipline &discipline : disciplines)
        disciplineComboBox->addItem(discipline.getName(), QVariant(discipline.getId()));

    createLayout();

    setHours();

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(flowComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setHours()));
    connect(disciplineComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setHours()));
}

void AddLoadcalculationDialog::addRow()
{
    if (DbService::getInstance()->addLoadCalculation(disciplineComboBox->itemData(disciplineComboBox->currentIndex()).toInt(),
                                                     flowComboBox->itemData(flowComboBox->currentIndex()).toInt()))
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Database error while adding a group."), QMessageBox::Ok);
}

void AddLoadcalculationDialog::createLayout()
{
    QFormLayout *formLayout = new QFormLayout(this);

    formLayout->addRow(tr("&Название потока:"), flowComboBox);
    formLayout->addRow(tr("&Название дисциплины:"), disciplineComboBox);
    formLayout->addRow(lecturesLabel, laboratoryLabel);
    formLayout->addRow(practicalLabel, consultationLabel);
    formLayout->addRow(examinationsLabel, testsLabel);
    formLayout->addRow(currentConsultationLabel, introductoryPracticeLabel);
    formLayout->addRow(preDiplomaPracticeLabel, courseworkLabel);
    formLayout->addRow(guidedIndependentWorkLabel, controlWorkLabel);
    formLayout->addRow(graduationDesignLabel, guideGraduateLabel);
    formLayout->addRow(stateExamLabel, hesLabel);
    formLayout->addRow(guideChairLabel, uirsLabel);
    formLayout->addRow(addButton);
    setLayout(formLayout);
}

void AddLoadcalculationDialog::setHours()
{
    Flow flow;
    Discipline discipline;

    for (Flow &flw : flows)
        if (flw.getId() == flowComboBox->itemData(flowComboBox->currentIndex()).toInt())
            flow = flw;

    for (Discipline &dsc : disciplines)
        if (dsc.getId() == disciplineComboBox->itemData(disciplineComboBox->currentIndex()).toInt())
            discipline = dsc;

    Factors factors = DbService::getInstance()->getFactors();
    int numberOfSudents = DbService::getInstance()->getStudentsNumberByFlowId(flow.getId());
    int numberOfSubGroups = DbService::getInstance()->getSubGroupsNumberByFlowId(flow.getId());

    lecturesLabel->setText(QString("Лекции: %1").arg(discipline.getLectures()));
    laboratoryLabel->setText(QString("Лабораторные: %1").arg(discipline.getLaboratory() * numberOfSubGroups));
    practicalLabel->setText(QString("Практические: %1").arg(discipline.getPractical()));
    consultationLabel->setText(QString("Консультации: %1").arg(factors.getConsultationFactor() * numberOfSudents * discipline.hasConsultation()));
    examinationsLabel->setText(QString("Экзамен: %1").arg(factors.getExaminationFactor() * numberOfSudents * discipline.hasExamination()));
    testsLabel->setText(QString("Зачет: %1").arg(factors.getTestsFactor() * numberOfSudents * discipline.hasTests()));
    currentConsultationLabel->setText(QString("Текущая консультация: %1").arg(factors.getCurrentConsultationFactor() * numberOfSudents * discipline.hasCurrentConsultation()));
    introductoryPracticeLabel->setText(QString("Ознакомительная практика: %1").arg(factors.getIntroductoryPracticeFactor() * numberOfSudents * discipline.hasIntroductoryPractice()));
    preDiplomaPracticeLabel->setText(QString("Преддипломная практика: %1").arg(factors.getPreDiplomaPracticeFactor() * numberOfSudents * discipline.hasPreDiplomaPractice()));
    courseworkLabel->setText(QString("Курсовая работа: %1").arg(factors.getCourseWorkFactor() * numberOfSudents * discipline.hasCourseWork()));
    guidedIndependentWorkLabel->setText(QString("Управляемая самост. работа: %1").arg(factors.getGuidedIndependentWorkFactor() * numberOfSudents * discipline.hasGuidedIndependentWork()));
    controlWorkLabel->setText(QString("Контрольная работа: %1").arg(factors.getControlWorkFactor() * numberOfSudents * discipline.hasControlWork()));
    graduationDesignLabel->setText(QString("Дипломное проектирование: %1").arg(factors.getGraduationDesignFactor() * numberOfSudents * discipline.hasGraduationDesign()));
    guideGraduateLabel->setText(QString("Рук-во аспирантами: %1").arg(factors.getGuideGraduateFactor() * numberOfSudents * discipline.hasGuideGraduate()));
    stateExamLabel->setText(QString("Гос экзамен: %1").arg(factors.getStateExamFactor() * numberOfSudents * discipline.hasStateExam()));
    hesLabel->setText(QString("ГЭК: %1").arg(factors.getHesFactor() * numberOfSudents * discipline.hasHes()));
    guideChairLabel->setText(QString("Руководство кафедрой: %1").arg(factors.getGuideChairFactor() * numberOfSudents * discipline.hasGuideChair()));
    uirsLabel->setText(QString("УИРС: %1").arg(factors.getUirsFactor() * numberOfSudents * discipline.hasUirs()));
}























