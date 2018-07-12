#ifndef ADDLOADDISTRIBUTIONDIALOG_H
#define ADDLOADDISTRIBUTIONDIALOG_H

#include "dialogs/loaddistribution_dialog.h"

#include <QMessageBox>


class AddLoadDistributionDialog : public LoadDistributionDialog
{
    Q_OBJECT
public:
    explicit AddLoadDistributionDialog(QWidget *parent = 0);

protected slots:
    virtual void saveRow();
    virtual void updateView();

};

#endif // ADDLOADDISTRIBUTIONDIALOG_H
