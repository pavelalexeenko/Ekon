#include "add_teacher_dialog.h"

AddTeacherDialog::AddTeacherDialog(QWidget *parent):
    QDialog(parent)
{
    nameLineEdit = new QLineEdit(this);
    rateSpinBox = new QDoubleSpinBox(this);
    notePlainTextEdit = new QPlainTextEdit(this);
    addButton = new QPushButton(QString("Добавить"), this);

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

    if (DbService::getInstance()->addTeacher(nameLineEdit->text(), rateSpinBox->value(), notePlainTextEdit->toPlainText()))
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Database error while adding a teacher."), QMessageBox::Ok);

}