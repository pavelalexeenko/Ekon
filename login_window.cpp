#include "login_window.h"
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent)
  , _databaseStatusLabel(new QLabel(this))
  , _credentialsGroupBox(new QGroupBox(this))
  , _usernameComboBox(new QComboBox(this))
  , _passwordLineEdit(new QLineEdit(this))
  , _loginButton(new QPushButton(QString("Login"), this))
  , _exitButton(new QPushButton(QString("Exit"), this))
  , _credentialsLayout(new QFormLayout(this))
  , _mainLayout(new QGridLayout(this))
  , _connectToAnotherDatabaseButton(new QPushButton(QString("Connect to another database"), this))
{
    connect(this, SIGNAL(accepted()), parent, SLOT(show()));
    connect(_loginButton, SIGNAL(clicked()), this, SLOT(login()));
    connect(_exitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(_connectToAnotherDatabaseButton, SIGNAL(clicked()), this, SLOT(connectToAnotherDatabase()));

    this->setWindowTitle(QString("Please login"));
    this->setWindowModality(Qt::ApplicationModal);

    _passwordLineEdit->setEchoMode(QLineEdit::Password);

    updateUsers();
    createLayout();
}

void LoginWindow::login()
{
    if (DbService::getInstance()->loginAs(_usernameComboBox->currentText(), _passwordLineEdit->text()))
        this->accept();
    else
        QMessageBox::critical(this, tr("Error"), tr("Wrong password."), QMessageBox::Ok);
}

void LoginWindow::connectToAnotherDatabase()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select database file"), "", tr("SQLite files (*.sqlite)"));

    DbService::getInstance()->connectToAnotherDatabase(fileName);
    updateUsers();
}

void LoginWindow::createLayout()
{
    _credentialsLayout->addRow(tr("Login:"), _usernameComboBox);
    _credentialsLayout->addRow(tr("Password:"), _passwordLineEdit);
    _credentialsGroupBox->setLayout(_credentialsLayout);

    _mainLayout->addWidget(_credentialsGroupBox, 0, 0, 1, 2);
    _mainLayout->addWidget(_loginButton, 1, 0);
    _mainLayout->addWidget(_exitButton, 1, 1);
    _mainLayout->addWidget(_databaseStatusLabel, 2, 0, 1, 2);
    _mainLayout->addWidget(_connectToAnotherDatabaseButton, 3, 0, 1, 2);

    this->setLayout(_mainLayout);
}

void LoginWindow::updateUsers()
{
    if (!DbService::getInstance()->isOpen())
    {
        _databaseStatusLabel->setText(QString("Failed to open the database."));
    }
    else
    {
        _databaseStatusLabel->setText(QString("Connected to: \"") + DbService::getInstance()->getCurrentDataBasePath() + QString("\""));
        _usernameComboBox->clear();
        _usernameComboBox->addItems(DbService::getInstance()->getAllUsers());
    }
}
