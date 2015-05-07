#include "load_distribution_widget.h"
#include "dialogs/add_loaddistribution_dialog.h"

LoadDistributionWidget::LoadDistributionWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << __FUNCTION__;

    QStringList columnNames;
    columnNames << "ID"
                << "ФИО преподавателя"
                << "Название\n дисциплины и потока"
                << "Лекции"
                << "Лабоработные"
                << "Практики"
                << "Консультации"
                << "Экзамен"
                << "Зачет"
                << "Текущая\n консультации"
                << "Ознакомительная\n практика"
                << "Преддипломная\n практика"
                << "Курсовая\n работа"
                << "Управляемая\n самост. работа"
                << "Контрольная\n работа"
                << "Дипломное\n проектирование"
                << "Рук-во\n аспирантами"
                << "Гос экзамен"
                << "ГЭК"
                << "Руководство\n кафедрой"
                << "УИРС";


    QList<QPair<int, QSqlRelation> > relations;
    relations.append(qMakePair(1, QSqlRelation("DRT_TEACHERS", "TCH_ID", "TCH_NAME")));
    relations.append(qMakePair(2, QSqlRelation("VIEW_LOAD_DISTRIBUTION_HELPER", "LDH_ID", "LDH_NAME")));

    loadDistributionTableModel = EkonTables::createRelationalTableModel(this, "DRT_LOAD_DISTRIBUTION", columnNames, relations);

    CheckableSortFilterProxyModel *cfpm = new CheckableSortFilterProxyModel(this);
    QList<int> readonlyCols;
    for (int i = 0; i < 21; i++)
        readonlyCols.append(i);

    cfpm->setParameters(QList<int>(), readonlyCols, QList<int>());
    cfpm->setSourceModel(loadDistributionTableModel);
    loadDistributionTableView = EkonTables::createTableView(this, cfpm);
    loadDistributionTableView->setItemDelegate(new QSqlRelationalDelegate(loadDistributionTableView));

    controlWidget = new ControlWidget(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(loadDistributionTableView);
    layout->addWidget(controlWidget);

    this->setLayout(layout);

    connect(controlWidget, SIGNAL(addRow()), this, SLOT(addRow()));
    connect(controlWidget, SIGNAL(filter(QString)), cfpm, SLOT(setFilterFixedString(QString)));
    connect(controlWidget, SIGNAL(search(QString)), cfpm, SLOT(setColorFilterString(QString)));
}

void LoadDistributionWidget::addRow()
{
    qDebug() << __FUNCTION__;
    AddLoadDistributionDialog *aldd = new AddLoadDistributionDialog(this);
    connect(aldd, SIGNAL(accepted()), this, SLOT(refresh()));
    aldd->exec();
}

void LoadDistributionWidget::refresh()
{
    qDebug() << __FUNCTION__;
    loadDistributionTableModel->select();
}
