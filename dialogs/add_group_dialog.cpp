#include "add_group_dialog.h"

AddGroupDialog::AddGroupDialog(QWidget *parent) :
    QDialog(parent)
    , nameLineEdit(new QLineEdit(this))
    , numberOfStudentsSpinBox(new QSpinBox(this))
    , courseSpinBox(new QSpinBox(this))
    , numberOfSubgroupsSpinBox(new QSpinBox(this))
    , semestrSpinBox(new QSpinBox(this))
    , facultyLineEdit(new QLineEdit(this))
    , specialityLineEdit(new QLineEdit(this))
    , notePlainTextEdit(new QPlainTextEdit(this))
    , addButton(new QPushButton(QString("Добавить"), this))
{
    qDebug() << __FUNCTION__;
    setWindowTitle("Добавление группы");

    courseSpinBox->setRange(1, 7);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));

    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow(tr("&Название группы:"), nameLineEdit);
    formLayout->addRow(tr("&Количество студентов:"), numberOfStudentsSpinBox);
    formLayout->addRow(tr("&Курс:"), courseSpinBox);
    formLayout->addRow(tr("&Количество подгрупп:"), numberOfSubgroupsSpinBox);
    formLayout->addRow(tr("&Семестр:"), semestrSpinBox);
    formLayout->addRow(tr("&Факультет:"), facultyLineEdit);
    formLayout->addRow(tr("&Специальность:"), specialityLineEdit);
    formLayout->addRow(tr("&Примечание:"), notePlainTextEdit);

    formLayout->addRow(tr(""), addButton);
    setLayout(formLayout);
}

void AddGroupDialog::addRow()
{
    qDebug() << __FUNCTION__;

    if (nameLineEdit->text().isEmpty() ||
            numberOfStudentsSpinBox->value() == 0 ||
            courseSpinBox->value() == 0 ||
            numberOfSubgroupsSpinBox->value() == 0 ||
            semestrSpinBox->value() == 0 ||
            facultyLineEdit->text().isEmpty() ||
            specialityLineEdit->text().isEmpty())
    {
        QMessageBox::critical(this, tr("Error"), tr("Some fields are empty."), QMessageBox::Ok);
        return;
    }

    Group group;
    group.setName(nameLineEdit->text());
    group.setNumberOfStudents(numberOfStudentsSpinBox->value());
    group.setCourse(courseSpinBox->value());
    group.setNumberOfSubgroups(numberOfSubgroupsSpinBox->value());
    group.setSemestr(semestrSpinBox->value());
    group.setFaculty(facultyLineEdit->text());
    group.setSpeciality(specialityLineEdit->text());
    group.setNote(notePlainTextEdit->toPlainText());

    if (DbService::getInstance()->addGroup(group))
        this->accept();
    else
        QMessageBox::critical(this, tr("Ошибка"), tr("Такая группа уже существует."), QMessageBox::Ok);
}
