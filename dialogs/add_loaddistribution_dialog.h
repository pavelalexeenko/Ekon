#ifndef ADDLOADDISTRIBUTIONDIALOG_H
#define ADDLOADDISTRIBUTIONDIALOG_H

#include <database/db_service.h>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QDebug>

class AddLoadDistributionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddLoadDistributionDialog(QWidget *parent = 0);

private slots:
    void addRow();
    void changeLayout(int index);

private:
    QComboBox *loadcalculationComboBox;
    QComboBox *teacherComboBox;

    QPushButton *addButton;
};

#endif // ADDLOADDISTRIBUTIONDIALOG_H
