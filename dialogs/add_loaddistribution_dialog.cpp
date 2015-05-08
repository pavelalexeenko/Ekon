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
  , controlHoursWidget(new HoursWidget())
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
    if (0/*DbService::getInstance()->addLoadCalculation(disciplineComboBox->itemData(disciplineComboBox->currentIndex()).toInt(),
                                                                                             flowComboBox->itemData(flowComboBox->currentIndex()).toInt())*/)
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Database error while adding a group."), QMessageBox::Ok);
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
    secondFormLayout->addRow(tr("&Контрольная работа:"), controlHoursWidget);
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

        lecturesHoursWidget->setTotalHours(lcl.getLectures());
        laboratoryHoursWidget->setTotalHours(lcl.getLaboratory());
        practicalHoursWidget->setTotalHours(lcl.getPractical());
        consultationHoursWidget->setTotalHours(lcl.getConsultation());
        examinationsHoursWidget->setTotalHours(lcl.getExamination());
        testsHoursWidget->setTotalHours(lcl.getTests());
        currentConsultationHoursWidget->setTotalHours(lcl.getCurrentConsultation());
        introductoryPracticeHoursWidget->setTotalHours(lcl.getIntroductoryPractice());
        preDiplomaPracticeHoursWidget->setTotalHours(lcl.getPreDiplomaPractice());
        courseworkHoursWidget->setTotalHours(lcl.getCourseWork());
        guidedIndependentWorkHoursWidget->setTotalHours(lcl.getGuideIndependentWork());
        controlHoursWidget->setTotalHours(lcl.getControlWork());
        graduationDesignHoursWidget->setTotalHours(lcl.getGraduationDesign());
        guideGraduateHoursWidget->setTotalHours(lcl.getGuideGraduate());
        stateExamHoursWidget->setTotalHours(lcl.getStateExam());
        hesHoursWidget->setTotalHours(lcl.getHes());
        guideChairHoursWidget->setTotalHours(lcl.getGuideChair());
        uirsHoursWidget->setTotalHours(lcl.getUirs());

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
