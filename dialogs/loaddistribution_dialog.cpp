#include "loaddistribution_dialog.h"

LoadDistributionDialog::LoadDistributionDialog(QWidget *parent) :
    QDialog(parent)
  , loadcalculationComboBox(new QComboBox(this))
  , teacherComboBox(new QComboBox(this))
  , lecturesHoursWidget(new HoursWidget("Лекции:", this))
  , laboratoryHoursWidget(new HoursWidget("Лабораторные:", this))
  , practicalHoursWidget(new HoursWidget("Практические:", this))
  , consultationHoursWidget(new HoursWidget("Консультации:", this))
  , examinationsHoursWidget(new HoursWidget("Экзамен:", this))
  , testsHoursWidget(new HoursWidget("Зачет:", this))
  , currentConsultationHoursWidget(new HoursWidget("Текущая консультация:", this))
  , introductoryPracticeHoursWidget(new HoursWidget("Ознакомительная практика:", this))
  , preDiplomaPracticeHoursWidget(new HoursWidget("Преддипломная практика:", this))
  , courseworkHoursWidget(new HoursWidget("Курсовая работа:", this))
  , guidedIndependentWorkHoursWidget(new HoursWidget("Управляемая самост. работа:", this))
  , controlWorkHoursWidget(new HoursWidget("Контрольная работа:", this))
  , graduationDesignHoursWidget(new HoursWidget("Дипломное проектирование:", this))
  , guideGraduateHoursWidget(new HoursWidget("Рук-во аспирантами:", this))
  , stateExamHoursWidget(new HoursWidget("Гос экзамен:", this))
  , hesHoursWidget(new HoursWidget("ГЭК:", this))
  , guideChairHoursWidget(new HoursWidget("Руководство кафедрой:", this))
  , uirsHoursWidget(new HoursWidget("УИРС:", this))
  , addButton(new QPushButton(this))
{
    qDebug() << __FUNCTION__;

    createLayout();
    fillLclCombo();
    setConnections();
}

void LoadDistributionDialog::setConnections()
{
    qDebug() << __FUNCTION__;

    connect(addButton, SIGNAL(clicked()), this, SLOT(saveRow()));
    connect(teacherComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateView()));
    connect(loadcalculationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateView()));
}

void LoadDistributionDialog::setHours(LoadCalculation notDistributedLcl, LoadCalculation totalLcl, LoadDistribution currentLoadDistribution)
{
    qDebug() << __FUNCTION__;

    lecturesHoursWidget->setHours(notDistributedLcl.getLectures(), totalLcl.getLectures(), currentLoadDistribution.getLectures());
    laboratoryHoursWidget->setHours(notDistributedLcl.getLaboratory(), totalLcl.getLaboratory(), currentLoadDistribution.getLaboratory());
    practicalHoursWidget->setHours(notDistributedLcl.getPractical(), totalLcl.getPractical(), currentLoadDistribution.getPractical());
    consultationHoursWidget->setHours(notDistributedLcl.getConsultation(), totalLcl.getConsultation(), currentLoadDistribution.getConsultation());
    examinationsHoursWidget->setHours(notDistributedLcl.getExamination(), totalLcl.getExamination(), currentLoadDistribution.getExamination());
    testsHoursWidget->setHours(notDistributedLcl.getTests(), totalLcl.getTests(), currentLoadDistribution.getTests());
    currentConsultationHoursWidget->setHours(notDistributedLcl.getCurrentConsultation(), totalLcl.getCurrentConsultation(), currentLoadDistribution.getCurrentConsultation());
    introductoryPracticeHoursWidget->setHours(notDistributedLcl.getIntroductoryPractice(), totalLcl.getIntroductoryPractice(), currentLoadDistribution.getIntroductoryPractice());
    preDiplomaPracticeHoursWidget->setHours(notDistributedLcl.getPreDiplomaPractice(), totalLcl.getPreDiplomaPractice(), currentLoadDistribution.getPreDiplomaPractice());
    courseworkHoursWidget->setHours(notDistributedLcl.getCourseWork(), totalLcl.getCourseWork(), currentLoadDistribution.getCourseWork());
    guidedIndependentWorkHoursWidget->setHours(notDistributedLcl.getGuideIndependentWork(), totalLcl.getGuideIndependentWork(), currentLoadDistribution.getGuideIndependentWork());
    controlWorkHoursWidget->setHours(notDistributedLcl.getControlWork(), totalLcl.getControlWork(), currentLoadDistribution.getControlWork());
    graduationDesignHoursWidget->setHours(notDistributedLcl.getGraduationDesign(), totalLcl.getGraduationDesign(), currentLoadDistribution.getGraduationDesign());
    guideGraduateHoursWidget->setHours(notDistributedLcl.getGuideGraduate(), totalLcl.getGuideGraduate(), currentLoadDistribution.getGuideGraduate());
    stateExamHoursWidget->setHours(notDistributedLcl.getStateExam(), totalLcl.getStateExam(), currentLoadDistribution.getStateExam());
    hesHoursWidget->setHours(notDistributedLcl.getHes(), totalLcl.getHes(), currentLoadDistribution.getHes());
    guideChairHoursWidget->setHours(notDistributedLcl.getGuideChair(), totalLcl.getGuideChair(), currentLoadDistribution.getGuideChair());
    uirsHoursWidget->setHours(notDistributedLcl.getUirs(), totalLcl.getUirs(), currentLoadDistribution.getUirs());
}

void LoadDistributionDialog::createLayout()
{
    qDebug() << __FUNCTION__;

    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow(tr("&Название потоковой дисциплины:"), loadcalculationComboBox);
    formLayout->addRow(tr("&Имя преподавателя:"), teacherComboBox);

    QGridLayout *hoursLayout = new QGridLayout();
    hoursLayout->addWidget(lecturesHoursWidget, 0, 0);
    hoursLayout->addWidget(laboratoryHoursWidget, 1, 0);
    hoursLayout->addWidget(practicalHoursWidget, 2, 0);
    hoursLayout->addWidget(consultationHoursWidget, 3, 0);
    hoursLayout->addWidget(examinationsHoursWidget, 4, 0);
    hoursLayout->addWidget(testsHoursWidget, 5, 0);
    hoursLayout->addWidget(currentConsultationHoursWidget, 6, 0);
    hoursLayout->addWidget(introductoryPracticeHoursWidget, 7, 0);
    hoursLayout->addWidget(preDiplomaPracticeHoursWidget, 8, 0);
    hoursLayout->addWidget(courseworkHoursWidget, 0, 1);
    hoursLayout->addWidget(guidedIndependentWorkHoursWidget, 1, 1);
    hoursLayout->addWidget(controlWorkHoursWidget, 2, 1);
    hoursLayout->addWidget(graduationDesignHoursWidget, 3, 1);
    hoursLayout->addWidget(guideGraduateHoursWidget, 4, 1);
    hoursLayout->addWidget(stateExamHoursWidget, 5, 1);
    hoursLayout->addWidget(hesHoursWidget, 6, 1);
    hoursLayout->addWidget(guideChairHoursWidget, 7, 1);
    hoursLayout->addWidget(uirsHoursWidget, 8, 1);

    formLayout->addRow(hoursLayout);
    formLayout->addRow(addButton);
    setLayout(formLayout);
}

void LoadDistributionDialog::fillLclCombo()
{
    QList<QPair<int, QString> > lclIdsAndNames = DbService::getInstance()->getLoadCalculationIdsAndNames();

    for (QPair<int, QString> &item : lclIdsAndNames)
        loadcalculationComboBox->addItem(item.second, QVariant(item.first));
}

LoadDistribution LoadDistributionDialog::getLoadDistribution()
{
    qDebug() << __FUNCTION__;

    LoadDistribution ld;
    ld.setTeacherId(teacherComboBox->itemData(teacherComboBox->currentIndex()).toInt());
    ld.setLoadCalculaionId(loadcalculationComboBox->itemData(loadcalculationComboBox->currentIndex()).toInt());
    ld.setLectures(lecturesHoursWidget->getHours());
    ld.setLaboratory(laboratoryHoursWidget->getHours());
    ld.setPractical(practicalHoursWidget->getHours());
    ld.setConsultation(consultationHoursWidget->getHours());
    ld.setExaminations(examinationsHoursWidget->getHours());
    ld.setTests(testsHoursWidget->getHours());
    ld.setCurrentConsultation(currentConsultationHoursWidget->getHours());
    ld.setIntroductoryPractice(introductoryPracticeHoursWidget->getHours());
    ld.setPreDiplomaPractice(preDiplomaPracticeHoursWidget->getHours());
    ld.setCourseWork(courseworkHoursWidget->getHours());
    ld.setGuideIndependentWork(guidedIndependentWorkHoursWidget->getHours());
    ld.setControlWork(controlWorkHoursWidget->getHours());
    ld.setGraduationDesign(graduationDesignHoursWidget->getHours());
    ld.setGuideGraduate(guideGraduateHoursWidget->getHours());
    ld.setStateExam(stateExamHoursWidget->getHours());
    ld.setHes(hesHoursWidget->getHours());
    ld.setGuideChair(guideChairHoursWidget->getHours());
    ld.setUirs(uirsHoursWidget->getHours());

    return ld;
}
