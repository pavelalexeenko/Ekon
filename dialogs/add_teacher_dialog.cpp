#include "add_teacher_dialog.h"

AddTeacherDialog::AddTeacherDialog(QWidget *parent):
    QDialog(parent)
    , nameLineEdit(new QLineEdit(this))
    , rateSpinBox(new QDoubleSpinBox(this))
    , notePlainTextEdit(new QPlainTextEdit(this))
    , addButton(new QPushButton(QString("Добавить"), this))
{
    setWindowTitle("Добавление преподавателя");

    rateSpinBox->setRange(0, 2);
    rateSpinBox->setSingleStep(0.25);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));

    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow(tr("&ФИО:"), nameLineEdit);
    formLayout->addRow(tr("&Ставка:"), rateSpinBox);
    formLayout->addRow(tr("&Примечание:"), notePlainTextEdit);
    formLayout->addRow(tr(""), addButton);
    setLayout(formLayout);
}

void AddTeacherDialog::addRow()
{
    qDebug() << __FUNCTION__;

    if (nameLineEdit->text().isEmpty() ||
            rateSpinBox->value() == 0 ||
            notePlainTextEdit->toPlainText().isEmpty())
    {
        QMessageBox::critical(this, tr("Error"), tr("Some fields are empty."), QMessageBox::Ok);
        return;
    }

    Teacher teacher;
    teacher.setName(nameLineEdit->text());
    teacher.setRate(rateSpinBox->value());
    teacher.setInfo(notePlainTextEdit->toPlainText());

    if (DbService::getInstance()->addTeacher(teacher))
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Database error while adding a teacher."), QMessageBox::Ok);

}
