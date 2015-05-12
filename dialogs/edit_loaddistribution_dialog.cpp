#include "edit_loaddistribution_dialog.h"
#include <QMutableListIterator>

EditLoadDistributionDialog::EditLoadDistributionDialog(QWidget *parent) :
    LoadDistributionDialog(parent)
{
    qDebug() << __FUNCTION__;
}

EditLoadDistributionDialog::EditLoadDistributionDialog(const int loadDistributionId, QWidget *parent) :
    LoadDistributionDialog(parent)
  , currentLoadDistributionId(loadDistributionId)
{
    qDebug() << __FUNCTION__;

    setWindowTitle("Изменение распределения учебной нагрузки");
    addButton->setText("&Изменить");

    QList<QPair<int, QString> > lclIdsAndNames = DbService::getInstance()->getLoadCalculationIdsAndNames();

    for (QPair<int, QString> &item : lclIdsAndNames)
        loadcalculationComboBox->addItem(item.second, QVariant(item.first));
}

void EditLoadDistributionDialog::saveRow()
{
    qDebug() << __FUNCTION__;

    LoadDistribution ld;

    ld.setId(currentLoadDistributionId);
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

    if (DbService::getInstance()->updateLoadDistribution(ld))
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Database error while updating a group."), QMessageBox::Ok);
}

void EditLoadDistributionDialog::updateView()
{
    qDebug() << __FUNCTION__;

    try
    {
        LoadDistribution currentLd = DbService::getInstance()->getLoadDistributionById(currentLoadDistributionId);

        if (QObject::sender() == teacherComboBox)
        {
            // fill lcls (don't need)
        }

        if (QObject::sender() == loadcalculationComboBox)
        {
            QList<Teacher> teachers = DbService::getInstance()->getAllTeachers();
            int selectedLclId = loadcalculationComboBox->itemData(loadcalculationComboBox->currentIndex()).toInt();
            QList<int> teachersThatAlreadyStudyWithLcl = DbService::getInstance()->getTeachersIdsForLoadCalculation(selectedLclId);

            QMutableListIterator<Teacher> i(teachers);
            while (i.hasNext())
            {
                Teacher teacher = i.next();
                if (teachersThatAlreadyStudyWithLcl.contains(teacher.getId()) && teacher.getId() != currentLd.getTeacherId())
                {
                    i.remove();
                }
            }

            teacherComboBox->clear();
            for (Teacher &teacher : teachers)
                teacherComboBox->addItem(teacher.getName(), QVariant(teacher.getId()));
        }

        int selectedLclId = loadcalculationComboBox->itemData(loadcalculationComboBox->currentIndex()).toInt();
        LoadCalculation totalLcl = DbService::getInstance()->getLoadCalculationById(selectedLclId);
        LoadCalculation notDistributedLcl = DbService::getInstance()->getNotDistributedLoadById(selectedLclId);

        if (currentLd.getLoadCalculaionId() == selectedLclId)
            setHours(notDistributedLcl, totalLcl, currentLd);
        else
            setHours(notDistributedLcl, totalLcl, LoadDistribution());

        this->updateGeometry();
    }
    catch (QString str)
    {
        QMessageBox::critical(this, tr("Error"), str, QMessageBox::Ok);
    }
}
