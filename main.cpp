#include "main_window.h"
#include "login_window.h"
#include "./database/db_service.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *mw = new MainWindow();
    LoginWindow *lw = new LoginWindow();
    QObject::connect(lw, SIGNAL(accepted()), mw, SLOT(show()));

    lw->show();

    int b;
    b = 2;
    
    return a.exec();
}
