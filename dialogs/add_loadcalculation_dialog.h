#ifndef ADD_LOADCALCULATION_DIALOG_H
#define ADD_LOADCALCULATION_DIALOG_H

#include <database/db_service.h>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QDebug>

class AddLoadcalculationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddLoadcalculationDialog(QWidget *parent = 0);
    
private slots:
    void addRow();

private:
    QComboBox *flowComboBox;
    QComboBox *disciplineComboBox;

    QPushButton *addButton;
};

#endif // ADD_LOADCALCULATION_DIALOG_H
