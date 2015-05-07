#include "add_loaddistribution_dialog.h"

AddLoadDistributionDialog::AddLoadDistributionDialog(QWidget *parent) :
    QDialog(parent)
  , loadcalculationComboBox(new QComboBox(this))
  , teacherComboBox(new QComboBox(this))
  , addButton(new QPushButton(this))
{
    qDebug() << __FUNCTION__;
    setWindowTitle("Добавление распределения учебной нагрузки");

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));

    QFormLayout *formLayout = new QFormLayout(this);

    formLayout->addRow(tr("&Название потоковой дисциплины:"), loadcalculationComboBox);
    formLayout->addRow(tr("&Имя преподавателя:"), teacherComboBox);
    formLayout->addRow(tr(""), addButton);
    setLayout(formLayout);

    QList<Flow> flows = DbService::getInstance()->getAllFlows();
    QList<Discipline> disciplines = DbService::getInstance()->getAllDisciplines();

//    for (Flow &flow : flows)
//        flowComboBox->addItem(flow.getName(), QVariant(flow.getId()));

//    for (Discipline &discipline : disciplines)
//        disciplineComboBox->addItem(discipline.getName(), QVariant(discipline.getId()));
}


void AddLoadDistributionDialog::addRow()
{
    if (0/*DbService::getInstance()->addLoadCalculation(disciplineComboBox->itemData(disciplineComboBox->currentIndex()).toInt(),
                                                     flowComboBox->itemData(flowComboBox->currentIndex()).toInt())*/)
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Database error while adding a group."), QMessageBox::Ok);
}
