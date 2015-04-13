#include "main_window.h"
#include "login_window.h"
#include "./database/db_service.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DbService::getInstance();
    MainWindow *mw = new MainWindow();
    mw->show();

    return a.exec();
}
