#include "add_loaddistribution_dialog.h"

AddLoadDistributionDialog::AddLoadDistributionDialog(QWidget *parent) :
    QDialog(parent)
  , loadcalculationComboBox(new QComboBox(this))
  , teacherComboBox(new QComboBox(this))
  , addButton(new QPushButton("&Добавить",this))
{
    qDebug() << __FUNCTION__;
    setWindowTitle("Добавление распределения учебной нагрузки");

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));

    QFormLayout *formLayout = new QFormLayout(this);

    formLayout->addRow(tr("&Название потоковой дисциплины:"), loadcalculationComboBox);
    formLayout->addRow(tr("&Имя преподавателя:"), teacherComboBox);
    formLayout->addRow(tr(""), addButton);
    setLayout(formLayout);

    connect(loadcalculationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeLayout(int)));

    QList<LoadCalculation> lcls;
    QList<QPair<int, QString> > lclIdsAndNames;
    QList<Teacher> teachers;

    try
    {
        lcls = DbService::getInstance()->getAllLoadCalculation();
        lclIdsAndNames = DbService::getInstance()->getLoadCalculationIdsAndNames();
        teachers = DbService::getInstance()->getAllTeachers();
    }
    catch(QString str)
    {
        QMessageBox::critical(this, tr("Database error"), str, QMessageBox::Ok);
    }

    for (QPair<int, QString> &item : lclIdsAndNames)
        loadcalculationComboBox->addItem(item.second, QVariant(item.first));

    for (Teacher &teacher : teachers)
        teacherComboBox->addItem(teacher.getName(), QVariant(teacher.getId()));

}


void AddLoadDistributionDialog::addRow()
{
    if (0/*DbService::getInstance()->addLoadCalculation(disciplineComboBox->itemData(disciplineComboBox->currentIndex()).toInt(),
                                                             flowComboBox->itemData(flowComboBox->currentIndex()).toInt())*/)
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Database error while adding a group."), QMessageBox::Ok);
}

void AddLoadDistributionDialog::changeLayout(int index)
{

}
