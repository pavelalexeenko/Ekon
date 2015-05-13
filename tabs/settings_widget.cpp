#include "settings_widget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent)
  , consultationDoubleSpinBox(new QDoubleSpinBox(this))
  , examinationDoubleSpinBox(new QDoubleSpinBox(this))
  , testsDoubleSpinBox(new QDoubleSpinBox(this))
  , currentConsultationDoubleSpinBox(new QDoubleSpinBox(this))
  , introductoryPracticeDoubleSpinBox(new QDoubleSpinBox(this))
  , preDiplomaPracticeDoubleSpinBox(new QDoubleSpinBox(this))
  , courseWorkDoubleSpinBox(new QDoubleSpinBox(this))
  , guidedIndependentWorkDoubleSpinBox(new QDoubleSpinBox(this))
  , controlWorkDoubleSpinBox(new QDoubleSpinBox(this))
  , graduationDesignDoubleSpinBox(new QDoubleSpinBox(this))
  , guideGraduateDoubleSpinBox(new QDoubleSpinBox(this))
  , stateExamDoubleSpinBox(new QDoubleSpinBox(this))
  , hesDoubleSpinBox(new QDoubleSpinBox(this))
  , guideChairDoubleSpinBox(new QDoubleSpinBox(this))
  , uirsDoubleSpinBox(new QDoubleSpinBox(this))
{
    createLayout();
    createMapper();
}

void SettingsWidget::createLayout()
{
    qDebug() << __FUNCTION__;

    QFormLayout *formLayout = new QFormLayout(this);

    QFormLayout *firstFormLayout = new QFormLayout();
    firstFormLayout->addRow(tr("&Консультации:"), consultationDoubleSpinBox);
    firstFormLayout->addRow(tr("&Экзамен:"), examinationDoubleSpinBox);
    firstFormLayout->addRow(tr("&Зачет:"), testsDoubleSpinBox);
    firstFormLayout->addRow(tr("&Текущая консультация:"), currentConsultationDoubleSpinBox);
    firstFormLayout->addRow(tr("&Ознакомительная практика:"), introductoryPracticeDoubleSpinBox);
    firstFormLayout->addRow(tr("&Преддипломная практика:"), preDiplomaPracticeDoubleSpinBox);
    firstFormLayout->addRow(tr("&Курсовая работа:"), courseWorkDoubleSpinBox);
    firstFormLayout->addRow(tr("&Управляемая самост. работа:"), guidedIndependentWorkDoubleSpinBox);
    firstFormLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QFormLayout *secondFormLayout = new QFormLayout();
    secondFormLayout->addRow(tr("&Контрольная работа:"), controlWorkDoubleSpinBox);
    secondFormLayout->addRow(tr("&Дипломное проектирование:"), graduationDesignDoubleSpinBox);
    secondFormLayout->addRow(tr("&Рук-во аспирантами:"), guideGraduateDoubleSpinBox);
    secondFormLayout->addRow(tr("&Гос экзамен:"), stateExamDoubleSpinBox);
    secondFormLayout->addRow(tr("&ГЭК:"), hesDoubleSpinBox);
    secondFormLayout->addRow(tr("&Руководство кафедрой:"), guideChairDoubleSpinBox);
    secondFormLayout->addRow(tr("&УИРС:"), uirsDoubleSpinBox);
    secondFormLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QHBoxLayout *lay = new QHBoxLayout();
    lay->addLayout(firstFormLayout);
    lay->addLayout(secondFormLayout);

    formLayout->addRow(lay);
    formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    formLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
}

void SettingsWidget::createMapper()
{
    QSqlTableModel *factorsModel = new QSqlTableModel(this, DbService::getInstance()->getCurrentDatabase());
    factorsModel->setTable("DRT_FACTORS");
    factorsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    factorsModel->select();

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(factorsModel);
    mapper->addMapping(consultationDoubleSpinBox, 1);
    mapper->addMapping(examinationDoubleSpinBox, 2);
    mapper->addMapping(testsDoubleSpinBox, 3);

    mapper->addMapping(uirsDoubleSpinBox, 15);
    mapper->toFirst();
}
