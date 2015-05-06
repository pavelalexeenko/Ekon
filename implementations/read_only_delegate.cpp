#include "read_only_delegate.h"

ReadOnlyDelegate::ReadOnlyDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

QWidget *ReadOnlyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QWidget *editor = new QWidget(parent);
    return editor;
}

void ReadOnlyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //QString value = index.model()->data(index, Qt::EditRole).toString();

    //QLabel *label = static_cast<QLabel*>(editor);
    //label->setText(value);
}

void ReadOnlyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //editor->setGeometry(option.rect);
}

void ReadOnlyDelegate::commitAndCloseEditor()
{
    QWidget *editor = qobject_cast<QWidget *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
