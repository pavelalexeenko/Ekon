#include "add_loadcalculation_dialog.h"

AddLoadcalculationDialog::AddLoadcalculationDialog(QWidget *parent) :
    QDialog(parent)
  , flowComboBox(new QComboBox(this))
  , disciplineComboBox(new QComboBox(this))
  , lecturesLabel(new QLabel(this))
  , laboratoryLabel(new QLabel(this))
  , practicalLabel(new QLabel(this))
  , consultationLabel(new QLabel(this))
  , examinationsLabel(new QLabel(this))
  , testsLabel(new QLabel(this))
  , currentConsultationLabel(new QLabel(this))
  , introductoryPracticeLabel(new QLabel(this))
  , preDiplomaPracticeLabel(new QLabel(this))
  , courseworkLabel(new QLabel(this))
  , guidedIndependentWorkLabel(new QLabel(this))
  , controlWorkLabel(new QLabel(this))
  , graduationDesignLabel(new QLabel(this))
  , guideGraduateLabel(new QLabel(this))
  , stateExamLabel(new QLabel(this))
  , hesLabel(new QLabel(this))
  , guideChairLabel(new QLabel(this))
  , uirsLabel(new QLabel(this))
  , addButton(new QPushButton("Добавить", this))
{
    qDebug() << __FUNCTION__;
    setWindowTitle("Добавление расчета нагрузки");

    flows = DbService::getInstance()->getAllFlows();
    disciplines = DbService::getInstance()->getAllDisciplines();

    for (Flow &flow : flows)
        flowComboBox->addItem(flow.getName(), QVariant(flow.getId()));

    for (Discipline &discipline : disciplines)
        disciplineComboBox->addItem(discipline.getName(), QVariant(discipline.getId()));

    createLayout();

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));
}

void AddLoadcalculationDialog::addRow()
{
    if (DbService::getInstance()->addLoadCalculation(disciplineComboBox->itemData(disciplineComboBox->currentIndex()).toInt(),
                                                     flowComboBox->itemData(flowComboBox->currentIndex()).toInt()))
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Database error while adding a group."), QMessageBox::Ok);
}

void AddLoadcalculationDialog::createLayout()
{
    QFormLayout *formLayout = new QFormLayout(this);

    formLayout->addRow(tr("&Название потока:"), flowComboBox);
    formLayout->addRow(tr("&Название дисциплины:"), disciplineComboBox);
    formLayout->addRow(lecturesLabel, laboratoryLabel);
    formLayout->addRow(practicalLabel, consultationLabel);
    formLayout->addRow(examinationsLabel, testsLabel);
    formLayout->addRow(currentConsultationLabel, introductoryPracticeLabel);
    formLayout->addRow(preDiplomaPracticeLabel, courseworkLabel);
    formLayout->addRow(courseworkLabel, guidedIndependentWorkLabel);
    formLayout->addRow(controlWorkLabel, graduationDesignLabel);
    formLayout->addRow(guideGraduateLabel, stateExamLabel);
    formLayout->addRow(hesLabel, guideChairLabel);
    formLayout->addRow(uirsLabel, new QLabel());
    formLayout->addRow(addButton);
    setLayout(formLayout);
}

void AddLoadcalculationDialog::setHours()
{
    Flow;
}
