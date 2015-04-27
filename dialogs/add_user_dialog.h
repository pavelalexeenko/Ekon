#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <database/db_service.h>

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>
#include <QDebug>

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = 0);

private slots:
    void addRow();

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QComboBox *userrolesComboBox;

    QPushButton *addButton;
};

#endif // ADDUSERDIALOG_H
