#include "add_loadcalculation_dialog.h"

AddLoadcalculationDialog::AddLoadcalculationDialog(QWidget *parent) :
    QDialog(parent)
  , flowComboBox(new QComboBox(this))
  , disciplineComboBox(new QComboBox(this))
  , addButton(new QPushButton("Добавить", this))
{
    qDebug() << __FUNCTION__;
    setWindowTitle("Добавление расчета нагрузки");

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));

    QFormLayout *formLayout = new QFormLayout(this);

    formLayout->addRow(tr("&Название потока:"), flowComboBox);
    formLayout->addRow(tr("&Название дисциплины:"), disciplineComboBox);
    formLayout->addRow(tr(""), addButton);
    setLayout(formLayout);

    QList<Flow> flows = DbService::getInstance()->getAllFlows();
    QList<Discipline> disciplines = DbService::getInstance()->getAllDisciplines();

    for (Flow &flow : flows)
        flowComboBox->addItem(flow.getName(), QVariant(flow.getId()));

    for (Discipline &discipline : disciplines)
        disciplineComboBox->addItem(discipline.getName(), QVariant(discipline.getId()));
}

void AddLoadcalculationDialog::addRow()
{
    if (DbService::getInstance()->addLoadCalculation(disciplineComboBox->itemData(disciplineComboBox->currentIndex()).toInt(),
                                                     flowComboBox->itemData(flowComboBox->currentIndex()).toInt()))
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Database error while adding a group."), QMessageBox::Ok);
}
