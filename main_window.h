#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <./database/db_service.h>
#include <management_widget.h>
#include <login_window.h>

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QStackedLayout>
#include <QAction>
#include <QMenuBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    void refreshButtonClicked();

public slots:

private slots:
    void updateTitle();
    void goToLoginWindow();

private:
    void createLayout();
    void createMenu();

private:
    QMenu *fileMenu;
    QMenu *saveMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *refreshAct;
    QAction *exitAct;

    ManagementWidget *managementWidget;
};

#endif // MAIN_WINDOW_H
