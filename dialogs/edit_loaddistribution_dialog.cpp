#include "edit_loaddistribution_dialog.h"
#include <QMutableListIterator>

EditLoadDistributionDialog::EditLoadDistributionDialog(QWidget *parent) :
    LoadDistributionDialog(parent)
{
    qDebug() << __FUNCTION__;
}

EditLoadDistributionDialog::EditLoadDistributionDialog(const int loadDistributionId, QWidget *parent) :
    LoadDistributionDialog(parent)
  , currentLoadDistribution(DbService::getInstance()->getLoadDistributionById(loadDistributionId))
{
    qDebug() << "loadDistributionId = " << loadDistributionId;
    qDebug() << __FUNCTION__;
    setWindowTitle("Изменение распределения учебной нагрузки");
    addButton->setText("&Изменить");

    selectCurrentLcl();
}

void EditLoadDistributionDialog::saveRow()
{
    qDebug() << __FUNCTION__;

    LoadDistribution ld = getLoadDistribution();

    ld.setId(currentLoadDistribution.getId());
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
                if (teachersThatAlreadyStudyWithLcl.contains(teacher.getId()) && teacher.getId() != currentLoadDistribution.getTeacherId())
                    i.remove();
            }

            teacherComboBox->clear();
            for (Teacher &teacher : teachers)
            {
                if (currentLoadDistribution.getTeacherId() == teacher.getId() && currentLoadDistribution.getLoadCalculaionId() == selectedLclId)
                    teacherComboBox->addItem(QString("%1 (текущий)").arg(teacher.getName()), QVariant(teacher.getId()));
                else
                    teacherComboBox->addItem(teacher.getName(), QVariant(teacher.getId()));
            }
        }

        LoadCalculation totalLcl = DbService::getInstance()->getLoadCalculationById(selectedLclId);
        LoadCalculation notDistributedLcl = DbService::getInstance()->getNotDistributedLoadById(selectedLclId);

        if (currentLoadDistribution.getLoadCalculaionId() == selectedLclId)
            setHours(notDistributedLcl, totalLcl, currentLoadDistribution);
        else
            setHours(notDistributedLcl, totalLcl, LoadDistribution());

        this->updateGeometry();
    }
    catch (QString str)
    {
        QMessageBox::critical(this, tr("Error"), str, QMessageBox::Ok);
    }
}

void EditLoadDistributionDialog::selectCurrentLcl()
{
    qDebug() << __FUNCTION__;

    for (int i = 0; i < loadcalculationComboBox->count(); i++)
        if (loadcalculationComboBox->itemData(i).toInt() == currentLoadDistribution.getLoadCalculaionId())
        {
            loadcalculationComboBox->setCurrentIndex(i);
            loadcalculationComboBox->currentIndexChanged(i);
            qDebug() << i;
            break;
        }
}
