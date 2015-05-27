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
    this->setWindowTitle(QString("Сейчас в системе: ") + user->getUsername() + " - " + user->getUserroleAsString());

    createMenu();
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

    try
    {
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

        for (QString str : columnNames)
        {
            out << str.toUtf8() << "\t";
        }
        out << "\n";

        for (QString item : list)
        {
            out << item << "\n";
        }

        QMessageBox::information(this, tr("Операция завершена."), tr("Данные о итоговом расчете\nуспешно экспортированы."), QMessageBox::Ok);
    }
    catch(QString str)
    {
        QMessageBox::critical(this, tr("Error."), str, QMessageBox::Ok);
    }
}

void MainWindow::exportLd()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "/Нагрузка на преподавателей.xls",
                                                    tr("Excel (*.xls)"));

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Error"), tr("Can't create file"), QMessageBox::Ok);
        return;
    }

    try
    {
        QStringList list = DbService::getInstance()->exportLd();

        QStringList columnNames;
        columnNames << "Имя преподавателя"
                    << "Название дисциплины"
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

        for (QString str : columnNames)
        {
            out << str.toUtf8() << "\t";
        }
        out << "\n";

        for (QString item : list)
        {
            out << item << "\n";
            // qDebug() << item;
        }

        QMessageBox::information(this, tr("Операция завершена."), tr("Данные о учебной нагрузке\nуспешно экспортированы."), QMessageBox::Ok);
    }
    catch(QString str)
    {
        QMessageBox::critical(this, tr("Error."), str, QMessageBox::Ok);
    }
}

void MainWindow::createMenu()
{
    qDebug() << __FUNCTION__;
    menuBar()->clear();

    fileMenu = menuBar()->addMenu(tr("&Файл"));

    openAct = new QAction(tr("&Вход в систему"), this);
    fileMenu->addAction(openAct);
    connect(openAct, SIGNAL(triggered()), this, SLOT(goToLoginWindow()));

    fileMenu->addSeparator();

    exitAct = new QAction(tr("&Выход"), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    refreshAct = new QAction(tr("&Обновить данные"), this);
    menuBar()->addAction(refreshAct);
    connect(refreshAct, SIGNAL(triggered()), tablesWidget, SLOT(refresh()));


    exportMenu = menuBar()->addMenu(tr("&Экспорт"));

    exportLclAct = new QAction(tr("&Экспорт итогового расчета нагрузки"), this);
    exportMenu->addAction(exportLclAct);
    connect(exportLclAct, SIGNAL(triggered()), this, SLOT(exportLcl()));
    if (DbService::getInstance()->getCurrentUser()->getUserrole() == User::Userrole::SECRETARY)
    {
        exportLdAct = new QAction(tr("&Экспорт нагрузки на преподавателей"), this);
        exportMenu->addAction(exportLdAct);
        connect(exportLdAct, SIGNAL(triggered()), this, SLOT(exportLd()));
    }
}

void MainWindow::setUp()
{
    tablesWidget = new TablesWidget(this);
    setCentralWidget(tablesWidget);
    tablesWidget->updateLayout();
    this->resize(1300,500);
}
