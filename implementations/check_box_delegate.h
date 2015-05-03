#ifndef CHECK_BOX_DELEGATE_H
#define CHECK_BOX_DELEGATE_H

#include <QStyledItemDelegate>
#include <QApplication>
#include <QEvent>
#include <QMouseEvent>

class CheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CheckBoxDelegate(QObject *parent = 0);
    
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    
};

#endif // CHECK_BOX_DELEGATE_H
