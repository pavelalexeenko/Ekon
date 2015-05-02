#ifndef ADD_LOADCALCULATION_DIALOG_H
#define ADD_LOADCALCULATION_DIALOG_H

#include <database/db_service.h>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QFormLayout>
#include <QMessageBox>
#include <QDebug>

class AddLoadcalculationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddLoadcalculationDialog(QWidget *parent = 0);
    
private slots:
//    void addRow();
//    void addGroups();
//    void removeGroups();
//    void changeFlow();

private:
    QLineEdit *nameLineEdit;
    QListWidget *groupsListWidget;

    QPushButton *addGroupButton;
    QPushButton *removeGroupButton;

    QPushButton *addButton;

    int _id;
};

#endif // ADD_LOADCALCULATION_DIALOG_H
