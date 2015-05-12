#ifndef EDITLOADDISTRIBUTIONDIALOG_H
#define EDITLOADDISTRIBUTIONDIALOG_H

#include "dialogs/loaddistribution_dialog.h"

#include <QMessageBox>

class EditLoadDistributionDialog : public LoadDistributionDialog
{
    Q_OBJECT
private:
    explicit EditLoadDistributionDialog(QWidget *parent = 0);
public:
    explicit EditLoadDistributionDialog(const int loadDistributionId, QWidget *parent = 0);

protected slots:
    virtual void saveRow();
    virtual void updateView();


private:
    int currentLoadDistributionId;
};

#endif // EDITLOADDISTRIBUTIONDIALOG_H
