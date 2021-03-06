#include "add_user_dialog.h"

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent)
    , usernameLineEdit(new QLineEdit(this))
    , passwordLineEdit(new QLineEdit(this))
    , userrolesComboBox(new QComboBox(this))
    , addButton(new QPushButton(QString("Добавить"), this))
{
    qDebug() << __FUNCTION__;
    setWindowTitle("Добавление пользователя");

    userrolesComboBox->addItems(DbService::getInstance()->getAllUserroles());

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));

    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow(tr("&Имя:"), usernameLineEdit);
    formLayout->addRow(tr("&Пароль:"), passwordLineEdit);
    formLayout->addRow(tr("&Тип учетной записи:"), userrolesComboBox);
    formLayout->addRow(tr(""), addButton);
    setLayout(formLayout);
}

void AddUserDialog::addRow()
{
    qDebug() << __FUNCTION__;

    if (usernameLineEdit->text().isEmpty() ||
            passwordLineEdit->text().isEmpty() ||
            userrolesComboBox->currentText().isEmpty())
    {
        QMessageBox::critical(this, tr("Error"), tr("Some fields are empty."), QMessageBox::Ok);
        return;
    }

    User user;
    user.setUsername(usernameLineEdit->text());
    user.setPassword(passwordLineEdit->text());
    user.setUserrole(userrolesComboBox->currentText());

    try
    {
        if (DbService::getInstance()->addUser(user))
        {
            qDebug() << "User added succesfully (" << user.getUsername() << " - " << user.getPassword() << " - " << user.getUserroleAsString() << ")";
            this->accept();
        }
    }
    catch(QSqlError)
    {
        qDebug() << "There was a database error while adding an user";
        QMessageBox::critical(this, tr("Ошибка!"), "Такой пользователь уже существует", QMessageBox::Ok);
    }

}
