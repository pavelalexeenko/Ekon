#include "checkable_sort_filter_proxy_model.h"

CheckableSortFilterProxyModel::CheckableSortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
}

void CheckableSortFilterProxyModel::setParameters(QList<int> boolCols, QList<int> readonlyCols, QList<int> passwordCols)
{
    booleanSet.clear();
    readonlySet.clear();
    passwordSet.clear();

    if (!boolCols.isEmpty())
    {
        foreach(int column , boolCols)
            booleanSet.append(column);
    }

    if (!readonlyCols.isEmpty())
    {
        foreach(int column , readonlyCols)
            readonlySet.append(column);
    }

    if (!passwordCols.isEmpty())
    {
        foreach(int column , passwordCols)
            passwordSet.append(column);
    }

}

void CheckableSortFilterProxyModel::setNullAndNotNullColumns(QList<int> nullCols, QList<int> notNullCols)
{
    notNullSet.clear();
    nullSet.clear();

    if (!notNullCols.isEmpty())
    {
        // this only works when our model is a QSqlQueryModel subclass
        if (sourceModel()->inherits("QSqlQueryModel"))
        {
            foreach(int column , notNullCols)
                notNullSet.append(column);
        }
        invalidateFilter();
    }

    if (!nullCols.isEmpty())
    {
        // this only works when our model is a QSqlQueryModel subclass
        if (sourceModel()->inherits("QSqlQueryModel"))
        {
            foreach(int column , nullCols)
                nullSet.append(column);
        }
        invalidateFilter();
    }
}

bool CheckableSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex & source_parent) const
{
    if (!notNullSet.isEmpty())
    {
        QSqlQueryModel *m = static_cast<QSqlQueryModel*>(sourceModel());
        foreach (int column, notNullSet)
            if (m->record(source_row).isNull(column))
                return false;
    }

    if (!nullSet.isEmpty())
    {
        QSqlQueryModel *m = static_cast<QSqlQueryModel*>(sourceModel());
        foreach (int column, nullSet)
            if (!m->record(source_row).isNull(column))
                return false;
    }

    for (int i = 0; i < sourceModel()->columnCount(source_parent); i++)
    {
        QRegExp searchString = filterRegExp();
        searchString.setCaseSensitivity(Qt::CaseInsensitive);
        if (sourceModel()->data(sourceModel()->index(source_row, i, source_parent)).toString().contains(searchString))
            return true;
    }

    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

void CheckableSortFilterProxyModel::setColorFilterString(const QString filter)
{
    colorFilter = filter;
    setFilterFixedString(QString(""));
}

void CheckableSortFilterProxyModel::setFilterFixedString(const QString &pattern)
{
    colorFilter.clear();
    QSortFilterProxyModel::setFilterFixedString(pattern);
}

QVariant CheckableSortFilterProxyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (booleanSet.contains(index.column()) && (role == Qt::CheckStateRole || role == Qt::DisplayRole))
    {
        if (role == Qt::CheckStateRole)
            return index.data(Qt::EditRole).toBool() ? QVariant(Qt::Checked) : QVariant(Qt::Unchecked);
        else if (role == Qt::DisplayRole)
            return QVariant();
    }
    else if (passwordSet.contains(index.column()) && (role == Qt::DisplayRole))
    {
        return QVariant("*****");
    }
    else if (readonlySet.contains(index.column()) && (role == Qt::BackgroundRole))
    {
        return QColor(212, 208, 200);
    }
    else if (readonlySet.contains(index.column()) && (role == Qt::TextColorRole))
    {
        return QColor(0,0,0);
    }
    else if ((role == Qt::BackgroundRole) && !colorFilter.isEmpty() &&(sourceModel()->data(index).toString().contains(colorFilter, Qt::CaseInsensitive)))
    {
        return QColor(Qt::yellow);
    }
    else if (role == Qt::BackgroundRole && modifiedCells.contains(qMakePair(index.row(), index.column())))
    {
        return QColor(QColor("#CC3333"));
    }
    else
        return QSortFilterProxyModel::data(index,role);

    return QVariant();
}

bool CheckableSortFilterProxyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;

    if(booleanSet.contains(index.column()) && role == Qt::CheckStateRole)
    {
        QVariant data = (value.toInt() == Qt::Checked) ? QVariant(1) : QVariant (0);
        return QSortFilterProxyModel::setData(index, data, Qt::EditRole);
    }
    else if (role == Qt::EditRole)
    {
        QSortFilterProxyModel::setData(index,value,role);
        QVector<int> vec;
        vec.append(Qt::BackgroundRole);
        vec.append(Qt::EditRole);
        modifiedCells.insert(qMakePair(index.row(), index.column()));
        emit dataChanged(index, index, vec);
    }
    else
        return QSortFilterProxyModel::setData(index,value,role);

}

Qt::ItemFlags CheckableSortFilterProxyModel::flags(const QModelIndex & index) const
{
    if(!index.isValid())
        return Qt::ItemIsEnabled;

    if (booleanSet.contains(index.column()))
        return Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    else if (readonlySet.contains(index.column()))
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    else
        return QSortFilterProxyModel::flags(index);

}
