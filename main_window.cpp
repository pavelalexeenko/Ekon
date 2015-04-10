#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
  , _passwordLineEdit(new QLineEdit())
  , _loginButton(new QPushButton())
  , _mainLayout(new QGridLayout())
{
    createLayout();

    LoginWindow *lw = new LoginWindow(this);
    connect(lw, SIGNAL(accepted()), this, SLOT(updateTitle()));
    connect(_loginButton, SIGNAL(clicked()), lw, SLOT(show()));
}

void MainWindow::show()
{
    QWidget::show();
    this->updateTitle();
}

void MainWindow::updateTitle()
{
    this->setWindowTitle(QString("Logged as: ") + DbService::getInstance()->getCurrentUserType());
}

void MainWindow::createLayout()
{
    _mainLayout->addWidget(_passwordLineEdit, 0, 0);
    _mainLayout->addWidget(_loginButton, 1, 0);

    this->setLayout(_mainLayout);
    this->setFixedSize(500,300);
    this->updateTitle();
}
