#include "main_window.h"
#include "./database/db_service.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qDebug() << __FUNCTION__;
    QApplication a(argc, argv);

    qDebug() << "1";
    DbService::getInstance();
    qDebug() << "2";
    DbService::getInstance()->loginAs("secretary", "123");
    MainWindow *mw = new MainWindow();

    return a.exec();
}
