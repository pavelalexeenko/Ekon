#include "add_user_dialog.h"

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent)
{
    usernameLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);
    userRolesComboBox = new QComboBox(this);
    addButton = new QPushButton(QString("Добавить"), this);

    userRolesComboBox->addItems(DbService::getInstance()->getAllUserRoles());

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));

    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow(tr("&Name:"), usernameLineEdit);
    formLayout->addRow(tr("&Password:"), passwordLineEdit);
    formLayout->addRow(tr("&User type:"), userRolesComboBox);
    formLayout->addRow(tr(""), addButton);
    setLayout(formLayout);
}

void AddUserDialog::addRow()
{
    qDebug() << __FUNCTION__;

    if (usernameLineEdit->text().isEmpty() ||
            passwordLineEdit->text().isEmpty() ||
            userRolesComboBox->currentText().isEmpty())
    {
        QMessageBox::critical(this, tr("Error"), tr("Some fields are empty."), QMessageBox::Ok);
        return;
    }

    if (DbService::getInstance()->addUser(usernameLineEdit->text(), passwordLineEdit->text(), userRolesComboBox->currentText()))
    {
        qDebug() << "Login succesfully.";
        this->accept();
    }
    else
    {
        qDebug() << "There was a database error while adding an user";
        QMessageBox::critical(this, tr("Error"), "Database error while adding an user.", QMessageBox::Ok);
    }
}
