#include "main_window.h"
#include "./database/db_service.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    qDebug() << __FUNCTION__;
    QApplication a(argc, argv);

    //DbService::getInstance();
    //DbService::getInstance()->loginAs("admin", "123");
    MainWindow *mw = new MainWindow();

    return a.exec();
}
