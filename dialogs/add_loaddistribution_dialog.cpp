#include "add_loaddistribution_dialog.h"

AddLoadDistributionDialog::AddLoadDistributionDialog(QWidget *parent) :
    QDialog(parent)
  , loadcalculationComboBox(new QComboBox(this))
  , teacherComboBox(new QComboBox(this))
  , addButton(new QPushButton("&Добавить",this))
  , lecturesHoursWidget(new HoursWidget())
  , laboratoryHoursWidget(new HoursWidget())
  , practicalHoursWidget(new HoursWidget())
  , consultationHoursWidget(new HoursWidget())
  , examinationsHoursWidget(new HoursWidget())
  , testsHoursWidget(new HoursWidget())
  , currentConsultationHoursWidget(new HoursWidget())
  , introductoryPracticeHoursWidget(new HoursWidget())
  , preDiplomaPracticeHoursWidget(new HoursWidget())
  , courseworkHoursWidget(new HoursWidget())
  , guidedIndependentWorkHoursWidget(new HoursWidget())
  , controlWorkHoursWidget(new HoursWidget())
  , graduationDesignHoursWidget(new HoursWidget())
  , guideGraduateHoursWidget(new HoursWidget())
  , stateExamHoursWidget(new HoursWidget())
  , hesHoursWidget(new HoursWidget())
  , guideChairHoursWidget(new HoursWidget())
  , uirsHoursWidget(new HoursWidget())
{
    qDebug() << __FUNCTION__;

    createLayout();
    fillComboBoxes();

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(loadcalculationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setHours()));

    setHours();
}


void AddLoadDistributionDialog::addRow()
{
    qDebug() << __FUNCTION__;

    LoadDistribution ld;

    ld.setTeacherId(teacherComboBox->currentData().toInt());
    ld.setLoadCalculaionId(loadcalculationComboBox->currentData().toInt());
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

    if (DbService::getInstance()->addLoadDistribution(ld))
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Database error while adding a group."), QMessageBox::Ok);
}

void AddLoadDistributionDialog::fillComboBoxes()
{
    try
    {
        QList<QPair<int, QString> > lclIdsAndNames = DbService::getInstance()->getLoadCalculationIdsAndNames();
        QList<Teacher> teachers = DbService::getInstance()->getAllTeachers();

        for (QPair<int, QString> &item : lclIdsAndNames)
            loadcalculationComboBox->addItem(item.second, QVariant(item.first));

        for (Teacher &teacher : teachers)
            teacherComboBox->addItem(teacher.getName(), QVariant(teacher.getId()));
    }
    catch(QString str)
    {
        QMessageBox::critical(this, tr("Database error"), str, QMessageBox::Ok);
    }
}

void AddLoadDistributionDialog::setHours()
{
    qDebug() << __FUNCTION__;

    try
    {
        int selectedLclId = loadcalculationComboBox->currentData().toInt();
        LoadCalculation lcl = DbService::getInstance()->getLoadCalculationById(selectedLclId);
        LoadCalculation notDistributedLcl = DbService::getInstance()->getNotDistributedLoadById(selectedLclId);

        lecturesHoursWidget->setHours(notDistributedLcl.getLectures(), lcl.getLectures());
        laboratoryHoursWidget->setHours(notDistributedLcl.getLaboratory(), lcl.getLaboratory());
        practicalHoursWidget->setHours(notDistributedLcl.getPractical(), lcl.getPractical());
        consultationHoursWidget->setHours(notDistributedLcl.getConsultation(), lcl.getConsultation());
        examinationsHoursWidget->setHours(notDistributedLcl.getExamination(), lcl.getExamination());
        testsHoursWidget->setHours(notDistributedLcl.getTests(), lcl.getTests());
        currentConsultationHoursWidget->setHours(notDistributedLcl.getCurrentConsultation(), lcl.getCurrentConsultation());
        introductoryPracticeHoursWidget->setHours(notDistributedLcl.getIntroductoryPractice(), lcl.getIntroductoryPractice());
        preDiplomaPracticeHoursWidget->setHours(notDistributedLcl.getPreDiplomaPractice(), lcl.getPreDiplomaPractice());
        courseworkHoursWidget->setHours(notDistributedLcl.getCourseWork(), lcl.getCourseWork());
        guidedIndependentWorkHoursWidget->setHours(notDistributedLcl.getGuideIndependentWork(), lcl.getGuideIndependentWork());
        controlWorkHoursWidget->setHours(notDistributedLcl.getControlWork(), lcl.getControlWork());
        graduationDesignHoursWidget->setHours(notDistributedLcl.getGraduationDesign(), lcl.getGraduationDesign());
        guideGraduateHoursWidget->setHours(notDistributedLcl.getGuideGraduate(), lcl.getGuideGraduate());
        stateExamHoursWidget->setHours(notDistributedLcl.getStateExam(), lcl.getStateExam());
        hesHoursWidget->setHours(notDistributedLcl.getHes(), lcl.getHes());
        guideChairHoursWidget->setHours(notDistributedLcl.getGuideChair(), lcl.getGuideChair());
        uirsHoursWidget->setHours(notDistributedLcl.getUirs(), lcl.getUirs());

        this->updateGeometry();
    }
    catch(QString str)
    {
        QMessageBox::critical(this, tr("Error"), str, QMessageBox::Ok);
    }
    catch(...)
    {
    }
}

void AddLoadDistributionDialog::createLayout()
{
    setWindowTitle("Добавление распределения учебной нагрузки");

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
