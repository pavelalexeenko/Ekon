#include "add_loadcalculation_dialog.h"

AddLoadcalculationDialog::AddLoadcalculationDialog(QWidget *parent) :
    QDialog(parent)
  , flowComboBox(new QComboBox(this))
  , disciplineComboBox(new QComboBox(this))
  , addButton(new QPushButton("Добавить", this))
{
    setWindowTitle("Добавление ");

//    rateSpinBox->setRange(0, 2);
//    rateSpinBox->setSingleStep(0.25);

//    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));

//    QFormLayout *formLayout = new QFormLayout(this);
//    formLayout->addRow(tr("&ФИО:"), nameLineEdit);
//    formLayout->addRow(tr("&Ставка:"), rateSpinBox);
//    formLayout->addRow(tr("&Примечание:"), notePlainTextEdit);
//    formLayout->addRow(tr(""), addButton);
//    setLayout(formLayout);
}

void AddLoadcalculationDialog::addRow()
{

}
