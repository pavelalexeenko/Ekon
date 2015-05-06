#ifndef CHECKABLESORTFILTERPROXYMODEL_H
#define CHECKABLESORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QColor>
#include <QString>
#include <QFont>

class CheckableSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit CheckableSortFilterProxyModel(QObject *parent = 0);

    void setParameters(QList<int> boolCols, QList<int> readonlyCols, QList<int> passwordCols);
    void setNullAndNotNullColumns(QList<int> nullCols, QList<int> notNullCols);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex & index) const override;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex & source_parent) const override;

signals:

public slots:

private:
    QList<int> booleanSet;
    QList<int> passwordSet;
    QList<int> readonlySet;
    QList<int> notNullSet;
    QList<int> nullSet;

};
#endif // CHECKABLESORTFILTERPROXYMODEL_H
