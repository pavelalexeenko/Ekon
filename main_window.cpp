#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    tablesWidget = new TablesWidget(this);
    setCentralWidget(tablesWidget);
    createMenu();
}

void MainWindow::updateTitle()
{
    this->setWindowTitle(QString("Logged as: ") + DbService::getInstance()->getCurrentUserType());
}

void MainWindow::goToLoginWindow()
{
    LoginWindow *lw = new LoginWindow(this);
    connect(lw, SIGNAL(accepted()), this, SLOT(updateTitle()));
    lw->show();
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));

    openAct = new QAction(tr("&Login"), this);
    fileMenu->addAction(openAct);
    connect(openAct, SIGNAL(triggered()), this, SLOT(goToLoginWindow()));

    fileMenu->addSeparator();

    exitAct = new QAction(tr("E&xit"), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}
