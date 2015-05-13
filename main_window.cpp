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

void MainWindow::exportLcl()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "/Итоговый расчет.xls",
                                                    tr("Excel (*.xls)"));

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Error"), tr("Can't create file"), QMessageBox::Ok);
        return;
    }

    QStringList list = DbService::getInstance()->exportLcl();

    QStringList columnNames;
    columnNames << "Название дисциплины"
                << "Название потока"
                << "Лекции"
                << "Лабоработные"
                << "Практики"
                << "Консультации"
                << "Экзамен"
                << "Зачет"
                << "Текущая консультация"
                << "Ознакомительная практика"
                << "Преддипломная практика"
                << "Курсовая работа"
                << "Управляемая самост. работа"
                << "Контрольная работа"
                << "Дипломное проектирование"
                << "Рук-во аспирантами"
                << "Гос экзамен"
                << "ГЭК"
                << "Руководство кафедрой"
                << "УИРС";

    QTextStream out(&file);
    out.setCodec("Windows-1251");

    for (QString str : columnNames)
    {
        out << str.toUtf8() << "\t";
        qDebug() << str.toUtf8();
    }
    out << "\n";

    for (QString item : list)
    {
        out << item << "\n";
    }

    out << "The magic number is: " << 49 << "\n";

    QMessageBox::warning(this, tr("Succes!"), tr("Done."), QMessageBox::Ok);
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

    exportLclAct = new QAction(tr("&Export Load Calculation"), this);
    menuBar()->addAction(exportLclAct);
    connect(exportLclAct, SIGNAL(triggered()), this, SLOT(exportLcl()));
}

void MainWindow::setUp()
{
    tablesWidget = new TablesWidget(this);
    setCentralWidget(tablesWidget);
    tablesWidget->updateLayout();
    this->resize(1300,500);
}
