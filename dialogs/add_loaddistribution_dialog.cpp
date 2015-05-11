#include "add_loaddistribution_dialog.h"

AddLoadDistributionDialog::AddLoadDistributionDialog(QWidget *parent) :
    QDialog(parent)
  , loadcalculationComboBox(new QComboBox(this))
  , teacherComboBox(new QComboBox(this))
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
  , addButton(new QPushButton("&Добавить",this))
  , _id(-1)
{
    qDebug() << __FUNCTION__;

    setWindowTitle("Добавление распределения учебной нагрузки");
    createLayout();
    fillComboBoxes();

    setHours();
    setConnections();
    checkTeacher(true);
}

AddLoadDistributionDialog::AddLoadDistributionDialog(const int loadDistributionId, QWidget *parent):
    QDialog(parent)
  , loadcalculationComboBox(new QComboBox(this))
  , teacherComboBox(new QComboBox(this))
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
  , addButton(new QPushButton("&Изменить",this))
  , _id(loadDistributionId)
{
    qDebug() << __FUNCTION__;

    setWindowTitle("Изменение распределения учебной нагрузки");
    createLayout();
    fillComboBoxes();

    LoadDistribution currentLoadDistribution = DbService::getInstance()->getLoadDistributionById(_id);
    for (int i = 0; i < loadcalculationComboBox->count(); i++)
        if (loadcalculationComboBox->itemData(i).toInt() == currentLoadDistribution.getLoadCalculaionId())
        {
            loadcalculationComboBox->setCurrentIndex(i);
            qDebug() << i;
            break;
        }

    setHours();
    setConnections();
    checkTeacher(true);
}


void AddLoadDistributionDialog::saveRow()
{
    qDebug() << __FUNCTION__;

    LoadDistribution ld;

    if (-1 != _id)
        ld.setId(_id);

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

    if (-1 != _id)
    {
        if (DbService::getInstance()->updateLoadDistribution(ld))
            this->accept();
        else
            QMessageBox::critical(this, tr("Error"), tr("Database error while adding a group."), QMessageBox::Ok);
    }
    else
    {
        if (DbService::getInstance()->addLoadDistribution(ld))
            this->accept();
        else
            QMessageBox::critical(this, tr("Error"), tr("Database error while adding a group."), QMessageBox::Ok);
    }

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

void AddLoadDistributionDialog::setConnections()
{
    connect(addButton, SIGNAL(clicked()), this, SLOT(saveRow()));
    connect(loadcalculationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setHours()));
    connect(teacherComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(checkTeacher()));
    connect(loadcalculationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(checkTeacher()));
}

void AddLoadDistributionDialog::setHours()
{
    qDebug() << __FUNCTION__;

    try
    {
        int selectedLclId = loadcalculationComboBox->itemData(loadcalculationComboBox->currentIndex()).toInt();
        LoadCalculation totalLcl = DbService::getInstance()->getLoadCalculationById(selectedLclId);
        LoadCalculation notDistributedLcl = DbService::getInstance()->getNotDistributedLoadById(selectedLclId);

        if (_id != -1)
        {
            LoadDistribution currentLoadDistribution = DbService::getInstance()->getLoadDistributionById(_id);
            if (currentLoadDistribution.getLoadCalculaionId() == selectedLclId)
            {
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
            else
            {
                setEmptyHours(notDistributedLcl, totalLcl);
            }
        }
        else
        {
            setEmptyHours(notDistributedLcl, totalLcl);
        }

        this->updateGeometry();
    }
    catch(QString str)
    {
        QMessageBox::critical(this, tr("Error"), str, QMessageBox::Ok);
    }
    catch(...)
    {
        QMessageBox::critical(this, tr("Error"), tr("Something go wrong"), QMessageBox::Ok);
    }
}

void AddLoadDistributionDialog::checkTeacher(bool firstShow)
{
    int selectedLclId = loadcalculationComboBox->itemData(loadcalculationComboBox->currentIndex()).toInt();
    teachersThatAlreadyStudyWithLcl = DbService::getInstance()->getTeachersIdsForLoadCalculation(selectedLclId);

    int selectedTeacherId = teacherComboBox->itemData(teacherComboBox->currentIndex()).toInt();

    if (teachersThatAlreadyStudyWithLcl.contains(selectedTeacherId))
    {
        addButton->setEnabled(false);
        addButton->setToolTip("Выбранный преподаватель уже читает данную дисциплину!");
        if (!firstShow)
            QMessageBox::information(this, tr("Внимание"), tr("Выбранный преподаватель уже читает данную дисциплину!"), QMessageBox::Ok);
    }
    else
    {
        addButton->setEnabled(true);
        addButton->setToolTip("");
    }
}

void AddLoadDistributionDialog::setEmptyHours(LoadCalculation notDistributedLcl, LoadCalculation totalLcl)
{
    lecturesHoursWidget->setHours(notDistributedLcl.getLectures(), totalLcl.getLectures());
    laboratoryHoursWidget->setHours(notDistributedLcl.getLaboratory(), totalLcl.getLaboratory());
    practicalHoursWidget->setHours(notDistributedLcl.getPractical(), totalLcl.getPractical());
    consultationHoursWidget->setHours(notDistributedLcl.getConsultation(), totalLcl.getConsultation());
    examinationsHoursWidget->setHours(notDistributedLcl.getExamination(), totalLcl.getExamination());
    testsHoursWidget->setHours(notDistributedLcl.getTests(), totalLcl.getTests());
    currentConsultationHoursWidget->setHours(notDistributedLcl.getCurrentConsultation(), totalLcl.getCurrentConsultation());
    introductoryPracticeHoursWidget->setHours(notDistributedLcl.getIntroductoryPractice(), totalLcl.getIntroductoryPractice());
    preDiplomaPracticeHoursWidget->setHours(notDistributedLcl.getPreDiplomaPractice(), totalLcl.getPreDiplomaPractice());
    courseworkHoursWidget->setHours(notDistributedLcl.getCourseWork(), totalLcl.getCourseWork());
    guidedIndependentWorkHoursWidget->setHours(notDistributedLcl.getGuideIndependentWork(), totalLcl.getGuideIndependentWork());
    controlWorkHoursWidget->setHours(notDistributedLcl.getControlWork(), totalLcl.getControlWork());
    graduationDesignHoursWidget->setHours(notDistributedLcl.getGraduationDesign(), totalLcl.getGraduationDesign());
    guideGraduateHoursWidget->setHours(notDistributedLcl.getGuideGraduate(), totalLcl.getGuideGraduate());
    stateExamHoursWidget->setHours(notDistributedLcl.getStateExam(), totalLcl.getStateExam());
    hesHoursWidget->setHours(notDistributedLcl.getHes(), totalLcl.getHes());
    guideChairHoursWidget->setHours(notDistributedLcl.getGuideChair(), totalLcl.getGuideChair());
    uirsHoursWidget->setHours(notDistributedLcl.getUirs(), totalLcl.getUirs());
}

void AddLoadDistributionDialog::createLayout()
{
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
