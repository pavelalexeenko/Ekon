#ifndef CHECKBOX_ITEM_DELEGATE_H
#define CHECKBOX_ITEM_DELEGATE_H

#include <QStyledItemDelegate>
#include <QItemDelegate>

class CheckBoxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    Q_DISABLE_COPY(CheckBoxItemDelegate)

public:
    explicit CheckBoxItemDelegate(QObject * parent = Q_NULLPTR);
    virtual ~CheckBoxItemDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private Q_SLOTS:
    void slot_OnToggled();
};

#endif // CHECKBOX_ITEM_DELEGATE_H
