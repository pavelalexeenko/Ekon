#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    managementWidget = new ManagementWidget(this);
    setCentralWidget(managementWidget);
    createMenu();
    this->setFixedSize(1300, 500);
    updateTitle();
}

void MainWindow::updateTitle()
{
    qDebug() << "Updating title.";
    this->setWindowTitle(QString("Logged as: ") + DbService::getInstance()->getCurrentUser()->getUserName() + " - " + DbService::getInstance()->getCurrentUser()->getUserRoleAsString());
    managementWidget->updateLayout();
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

    exitAct = new QAction(tr("&Exit"), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    saveMenu = menuBar()->addMenu(tr("&Save"));

    saveAct = new QAction(tr("&Save"), this);
    saveMenu->addAction(saveAct);
    connect(saveAct, SIGNAL(triggered()), managementWidget, SLOT(updateLayout()));
}
