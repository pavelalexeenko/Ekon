#include "login_window.h"
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent)
  , _credentialsGroupBox(new QGroupBox(this))
  , _usernameComboBox(new QComboBox(this))
  , _passwordLineEdit(new QLineEdit(this))
  , _databaseStatusLabel(new QLabel(this))
  , _loginButton(new QPushButton(QString("Login"), this))
  , _exitButton(new QPushButton(QString("Exit"), this))
  , _connectToAnotherDatabaseButton(new QPushButton(QString("Connect to another database"), this))
  , _credentialsLayout(new QFormLayout(_credentialsGroupBox))
  , _mainLayout(new QGridLayout(this))
{
    qDebug() << __FUNCTION__;
    setWindowTitle(QString("Вход в систему"));
    setWindowModality(Qt::ApplicationModal);
    setWindowState(Qt::WindowActive);

    updateUsers();
    createLayout();

    _connectToAnotherDatabaseButton->hide();
    _databaseStatusLabel->hide();

    connect(this, SIGNAL(accepted()), parent, SLOT(show()));
    connect(_loginButton, SIGNAL(clicked()), this, SLOT(login()));
    connect(_exitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(_connectToAnotherDatabaseButton, SIGNAL(clicked()), this, SLOT(connectToAnotherDatabase()));
}

void LoginWindow::login()
{
    qDebug() << __FUNCTION__;

    if (DbService::getInstance()->loginAs(_usernameComboBox->currentText(), _passwordLineEdit->text()))
    {
        qDebug() << "Login succesfully.";
        this->accept();
    }
    else
    {
        qDebug() << "There was an error while loggining.";
        QMessageBox::critical(this, tr("Error"), tr("Wrong password."), QMessageBox::Ok);
    }
}

void LoginWindow::connectToAnotherDatabase()
{    
    qDebug() << __FUNCTION__;

    try
    {
        QString filename = QFileDialog::getOpenFileName(0, tr("Select database file"), "", tr("SQLite files (*.sqlite)"));
        DbService::getInstance()->connectToAnotherDatabase(filename);
        updateUsers();
    }
    catch (QString str)
    {
        qDebug() << "throw: " << str;
        QMessageBox::critical(this, tr("Error"), str, QMessageBox::Ok);
    }
}

void LoginWindow::createLayout()
{
    qDebug() << __FUNCTION__;

    _credentialsLayout->addRow(tr("Login:"), _usernameComboBox);
    _credentialsLayout->addRow(tr("Password:"), _passwordLineEdit);

    _mainLayout->addWidget(_credentialsGroupBox, 0, 0, 1, 2);
    _mainLayout->addWidget(_loginButton, 1, 0);
    _mainLayout->addWidget(_exitButton, 1, 1);
    _mainLayout->addWidget(_databaseStatusLabel, 2, 0, 1, 2);
    _mainLayout->addWidget(_connectToAnotherDatabaseButton, 3, 0, 1, 2);

    _passwordLineEdit->setEchoMode(QLineEdit::Password);
}

void LoginWindow::updateUsers()
{
    qDebug() << __FUNCTION__;

    if (!DbService::getInstance()->testDatabaseConnection())
    {
        qDebug() << "Failed to open the database.";
        _databaseStatusLabel->setText(QString("Failed to open the database."));
    }
    else
    {
        qDebug() << "Setting users list.";
        _databaseStatusLabel->setText(QString("Connected to: \"") + DbService::getInstance()->getCurrentDataBasePath() + QString("\""));
        _usernameComboBox->clear();
        _usernameComboBox->addItems(DbService::getInstance()->getAllUsers());
    }
}
