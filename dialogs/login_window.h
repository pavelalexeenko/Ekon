#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <./database/db_service.h>

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>

class LoginWindow : public QDialog
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = 0);

signals:
    void loginAs(int role);
    
public slots:

private slots:
    void login();
    void connectToAnotherDatabase();

private:
    void createLayout();
    void updateUsers();

private:
    QGroupBox *_credentialsGroupBox;
    QComboBox *_usernameComboBox;
    QLineEdit *_passwordLineEdit;
    QLabel *_databaseStatusLabel;
    QPushButton *_loginButton;
    QPushButton *_exitButton;
    QPushButton *_connectToAnotherDatabaseButton;

    QFormLayout *_credentialsLayout;
    QGridLayout *_mainLayout;
};

#endif // LOGIN_WINDOW_H
