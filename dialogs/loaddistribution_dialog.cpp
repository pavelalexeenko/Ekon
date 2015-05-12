#include "loaddistribution_dialog.h"

LoadDistributionDialog::LoadDistributionDialog(QWidget *parent) :
    QDialog(parent)
  , loadcalculationComboBox(new QComboBox(this))
  , teacherComboBox(new QComboBox(this))
  , lecturesHoursWidget(new HoursWidget(this))
  , laboratoryHoursWidget(new HoursWidget(this))
  , practicalHoursWidget(new HoursWidget(this))
  , consultationHoursWidget(new HoursWidget(this))
  , examinationsHoursWidget(new HoursWidget(this))
  , testsHoursWidget(new HoursWidget(this))
  , currentConsultationHoursWidget(new HoursWidget(this))
  , introductoryPracticeHoursWidget(new HoursWidget(this))
  , preDiplomaPracticeHoursWidget(new HoursWidget(this))
  , courseworkHoursWidget(new HoursWidget(this))
  , guidedIndependentWorkHoursWidget(new HoursWidget(this))
  , controlWorkHoursWidget(new HoursWidget(this))
  , graduationDesignHoursWidget(new HoursWidget(this))
  , guideGraduateHoursWidget(new HoursWidget(this))
  , stateExamHoursWidget(new HoursWidget(this))
  , hesHoursWidget(new HoursWidget(this))
  , guideChairHoursWidget(new HoursWidget(this))
  , uirsHoursWidget(new HoursWidget(this))
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

    QFormLayout *firstFormLayout = new QFormLayout();
    firstFormLayout->addRow(tr("&Лекции:"), lecturesHoursWidget);
    firstFormLayout->addRow(tr("&Лабораторные:"), laboratoryHoursWidget);
    firstFormLayout->addRow(tr("&Практические:"), practicalHoursWidget);
    firstFormLayout->addRow(tr("&Консультации:"), consultationHoursWidget);
    firstFormLayout->addRow(tr("&Экзамен:"), examinationsHoursWidget);
    firstFormLayout->addRow(tr("&Зачет:"), testsHoursWidget);
    firstFormLayout->addRow(tr("&Текущая консультация:"), currentConsultationHoursWidget);
    firstFormLayout->addRow(tr("&Ознакомительная практика:"), introductoryPracticeHoursWidget);
    firstFormLayout->addRow(tr("&Преддипломная практика:"), preDiplomaPracticeHoursWidget);
    firstFormLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QFormLayout *secondFormLayout = new QFormLayout();
    secondFormLayout->addRow(tr("&Курсовая работа:"), courseworkHoursWidget);
    secondFormLayout->addRow(tr("&Управляемая самост. работа:"), guidedIndependentWorkHoursWidget);
    secondFormLayout->addRow(tr("&Контрольная работа:"), controlWorkHoursWidget);
    secondFormLayout->addRow(tr("&Дипломное проектирование:"), graduationDesignHoursWidget);
    secondFormLayout->addRow(tr("&Рук-во аспирантами:"), guideGraduateHoursWidget);
    secondFormLayout->addRow(tr("&Гос экзамен:"), stateExamHoursWidget);
    secondFormLayout->addRow(tr("&ГЭК:"), hesHoursWidget);
    secondFormLayout->addRow(tr("&Руководство кафедрой:"), guideChairHoursWidget);
    secondFormLayout->addRow(tr("&УИРС:"), uirsHoursWidget);
    secondFormLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QHBoxLayout *lay = new QHBoxLayout();
    lay->addLayout(firstFormLayout);
    lay->addLayout(secondFormLayout);

    formLayout->addRow(lay);
    formLayout->addRow(addButton);
    formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    formLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);

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
