#ifndef ADDFLOWDIALOG_H
#define ADDFLOWDIALOG_H

#include <database/db_service.h>

#include <QWidget>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>
#include <QDebug>

class AddFlowDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddFlowDialog(QWidget *parent = 0);
    explicit AddFlowDialog(const int& id, QWidget *parent = 0);

private slots:
    void addRow();
    void addGroups();
    void removeGroups();
    void changeFlow();

private:
    QLineEdit *nameLineEdit;
    QListWidget *groupsListWidget;
    QPlainTextEdit *notePlainTextEdit;

    QPushButton *addGroupButton;
    QPushButton *removeGroupButton;

    QPushButton *addButton;

    int _id;
};

#endif // ADDFLOWDIALOG_H
