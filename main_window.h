#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <./database/db_service.h>
#include <tables_wigdet.h>
#include <dialogs/login_window.h>

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QStackedLayout>
#include <QAction>
#include <QMenuBar>
#include <QTextCodec>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

private slots:
    void updateTitle();
    void goToLoginWindow();
    void exportLcl();
    void exportLd();

private:
    void createMenu();
    void setUp();

private:
    QMenu *fileMenu;
    QMenu *exportMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *refreshAct;
    QAction *exitAct;
    QAction *exportLclAct;
    QAction *exportLdAct;

    TablesWidget *tablesWidget;
};

#endif // MAIN_WINDOW_H
