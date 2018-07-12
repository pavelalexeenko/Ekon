#ifndef CHECK_BOX_DELEGATE_H
#define CHECK_BOX_DELEGATE_H

#include <QStyledItemDelegate>
#include <QApplication>
#include <QEvent>
#include <QMouseEvent>
#include <QCheckBox>

class CheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CheckBoxDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
   // QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
   // void setEditorData(QWidget *editor, const QModelIndex &index) const;

};

#endif // CHECK_BOX_DELEGATE_H
