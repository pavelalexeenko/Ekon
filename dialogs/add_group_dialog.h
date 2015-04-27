#ifndef ADD_GROUP_DIALOG_H
#define ADD_GROUP_DIALOG_H

#include <database/db_service.h>

#include <QWidget>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>
#include <QDebug>

class AddGroupDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddGroupDialog(QWidget *parent = 0);
    
private slots:
    void addRow();

private:
    QLineEdit *nameLineEdit;
    QSpinBox *numberOfStudentsSpinBox;
    QSpinBox *courseSpinBox;
    QSpinBox *numberOfSubgroupsSpinBox;
    QSpinBox *semestrSpinBox;
    QLineEdit *facultyLineEdit;
    QLineEdit *specialityLineEdit;
    QPlainTextEdit *notePlainTextEdit;

    QPushButton *addButton;
};

#endif // ADD_GROUP_DIALOG_H
