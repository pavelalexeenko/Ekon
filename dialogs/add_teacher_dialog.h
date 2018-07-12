#ifndef ADDTEACHERDIALOG_H
#define ADDTEACHERDIALOG_H

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

class AddTeacherDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddTeacherDialog(QWidget *parent = 0);

private slots:
    void addRow();

private:
    QLineEdit *nameLineEdit;
    QDoubleSpinBox *rateSpinBox;
    QPlainTextEdit *notePlainTextEdit;

    QPushButton *addButton;
};

#endif // ADDTEACHERDIALOG_H
