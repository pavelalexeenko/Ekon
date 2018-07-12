#ifndef ADDGROUPTOFLOWDIALOG_H
#define ADDGROUPTOFLOWDIALOG_H

#include <database/db_service.h>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QFormLayout>
#include <QMessageBox>
#include <QDebug>

class AddGroupToFlowDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddGroupToFlowDialog(QWidget *parent = 0);

    QList<int> getSelectedGroupsId() const;

private slots:
    void setSelectedIds();

private:
    QListWidget *groupsListWidget;

    QPushButton *addButton;
    QPushButton *exitButton;

    QList<int> selectedIds;
};

#endif // ADDGROUPTOFLOWDIALOG_H
