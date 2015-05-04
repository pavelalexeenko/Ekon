#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    qDebug() << __FUNCTION__;
    tablesWidget = new TablesWidget(this);
    setCentralWidget(tablesWidget);
    createMenu();
    this->resize(1300,500);
    updateTitle();
    this->show();
    if (!DbService::getInstance()->isLogged())
    {
        this->hide();
        goToLoginWindow();
    }
}

void MainWindow::updateTitle()
{
    qDebug() << __FUNCTION__;
    QSharedPointer<User> user = DbService::getInstance()->getCurrentUser();
    this->setWindowTitle(QString("Logged as: ") + user->getUsername() + " - " + user->getUserroleAsString());
    tablesWidget->updateLayout();
}

void MainWindow::goToLoginWindow()
{
    qDebug() << __FUNCTION__;
    LoginWindow *lw = new LoginWindow(this);
    connect(lw, SIGNAL(accepted()), this, SLOT(updateTitle()));
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

    saveMenu = menuBar()->addMenu(tr("&Save"));

    saveAct = new QAction(tr("&Save"), this);
    saveMenu->addAction(saveAct);
    connect(saveAct, SIGNAL(triggered()), tablesWidget, SLOT(updateLayout()));

    refreshAct = new QAction(tr("&Refresh"), this);
    menuBar()->addAction(refreshAct);
    connect(refreshAct, SIGNAL(triggered()), tablesWidget, SLOT(refresh()));
}
