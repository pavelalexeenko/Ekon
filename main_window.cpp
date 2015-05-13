#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    qDebug() << __FUNCTION__;

    setUp();
    createMenu();
    updateTitle();

    //this->show();
    if (!DbService::getInstance()->isLogged())
        goToLoginWindow();
}

void MainWindow::updateTitle()
{
    qDebug() << __FUNCTION__;
    QSharedPointer<User> user = DbService::getInstance()->getCurrentUser();
    this->setWindowTitle(QString("Logged as: ") + user->getUsername() + " - " + user->getUserroleAsString());
}

void MainWindow::goToLoginWindow()
{
    qDebug() << __FUNCTION__;
    LoginWindow *lw = new LoginWindow(this);
    connect(lw, SIGNAL(accepted()), this, SLOT(updateTitle()));
    connect(lw, SIGNAL(accepted()), tablesWidget, SLOT(updateLayout()));
    this->hide();
    lw->show();
}

void MainWindow::createMenu()
{
    qDebug() << __FUNCTION__;
    fileMenu = menuBar()->addMenu(tr("&File"));

    openAct = new QAction(tr("&Login"), this);
    fileMenu->addAction(openAct);
    connect(openAct, SIGNAL(triggered()), this, SLOT(goToLoginWindow()));

    fileMenu->addSeparator();

    exitAct = new QAction(tr("&Exit"), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    refreshAct = new QAction(tr("&Refresh"), this);
    menuBar()->addAction(refreshAct);
    connect(refreshAct, SIGNAL(triggered()), tablesWidget, SLOT(refresh()));
}

void MainWindow::setUp()
{
    tablesWidget = new TablesWidget(this);
    setCentralWidget(tablesWidget);
    tablesWidget->updateLayout();
    this->resize(1300,500);
}
