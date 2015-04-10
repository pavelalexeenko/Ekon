#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <login_window.h>
#include <./database/db_service.h>

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void show();

private slots:
    void updateTitle();
    void goToLoginWindow();

private:
    void createLayout();

private:
    QLineEdit *_passwordLineEdit;
    QPushButton *_loginButton;

    QGridLayout *_mainLayout;
    
};

#endif // MAIN_WINDOW_H
