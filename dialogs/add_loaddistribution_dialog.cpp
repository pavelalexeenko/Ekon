#include "add_loaddistribution_dialog.h"

AddLoadDistributionDialog::AddLoadDistributionDialog(QWidget *parent) :
    LoadDistributionDialog(parent)
{
    qDebug() << __FUNCTION__;
    setWindowTitle("Добавление распределения учебной нагрузки");
    addButton->setText("&Добавить");

    if (loadcalculationComboBox->count() > 0)
        loadcalculationComboBox->setCurrentIndex(1);
}

void AddLoadDistributionDialog::saveRow()
{
    qDebug() << __FUNCTION__;

    LoadDistribution ld = getLoadDistribution();

    if (DbService::getInstance()->addLoadDistribution(ld))
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Database error while adding a group."), QMessageBox::Ok);
}

void AddLoadDistributionDialog::updateView()
{
    qDebug() << __FUNCTION__;

    try
    {
        int selectedLclId = loadcalculationComboBox->itemData(loadcalculationComboBox->currentIndex()).toInt();

        if (QObject::sender() == teacherComboBox)
        {
            // fill lcls (don't need)
        }

        if (QObject::sender() == loadcalculationComboBox)
        {
            QList<Teacher> teachers = DbService::getInstance()->getAllTeachers();
            QList<int> teachersThatAlreadyStudyWithLcl = DbService::getInstance()->getTeachersIdsForLoadCalculation(selectedLclId);

            QMutableListIterator<Teacher> i(teachers);
            while (i.hasNext())
            {
                Teacher teacher = i.next();
                if (teachersThatAlreadyStudyWithLcl.contains(teacher.getId()))
                    i.remove();
            }

            teacherComboBox->clear();
            for (Teacher &teacher : teachers)
                teacherComboBox->addItem(teacher.getName(), QVariant(teacher.getId()));
        }

        LoadCalculation totalLcl = DbService::getInstance()->getLoadCalculationById(selectedLclId);
        LoadCalculation notDistributedLcl = DbService::getInstance()->getNotDistributedLoadById(selectedLclId);
        setHours(notDistributedLcl, totalLcl, LoadDistribution());

        this->updateGeometry();
    }
    catch (QString str)
    {
        QMessageBox::critical(this, tr("Error"), str, QMessageBox::Ok);
    }
}
