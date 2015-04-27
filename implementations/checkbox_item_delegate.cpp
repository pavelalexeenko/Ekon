#include "checkbox_item_delegate.h"
#include "implementations/centered_checkbox.h"

#include <QApplication>
#include <QtGui/QMouseEvent>
#include <QCheckBox>
#include <QDebug>

namespace {
const bool defaultValue = false;
}

CheckBoxItemDelegate::CheckBoxItemDelegate(QObject *a_parent) :
    QStyledItemDelegate(a_parent)
{
}

CheckBoxItemDelegate::~CheckBoxItemDelegate()
{
}

QWidget *CheckBoxItemDelegate::createEditor(QWidget *a_parent, const QStyleOptionViewItem &a_option, const QModelIndex &a_index) const
{
    Q_UNUSED(a_option);
    Q_UNUSED(a_index);

    CenteredCheckBox *editor = new CenteredCheckBox(a_parent);
    editor->checkBox()->setChecked(::defaultValue);

    QCheckBox *chkEditor = editor->checkBox();
    connect(chkEditor, SIGNAL(pressed()), this, SLOT(slot_OnToggled()));

    return editor;
}

void CheckBoxItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QVariant data = index.model()->data(index, Qt::EditRole);

    bool value = false;

    if (!data.isNull())
        value = data.toBool();
    else
        value = defaultValue;

    CenteredCheckBox *checkBoxWidget = static_cast<CenteredCheckBox*>(editor);
    checkBoxWidget->checkBox()->setChecked(value);
}

void CheckBoxItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    CenteredCheckBox *checkBoxWidget = static_cast<CenteredCheckBox*>(editor);
    bool value = checkBoxWidget->checkBox()->isChecked();

    model->setData(index, value, Qt::EditRole);
}

void CheckBoxItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

void CheckBoxItemDelegate::paint(QPainter *a_painter, const QStyleOptionViewItem &a_option, const QModelIndex &a_index) const
{
    QVariant value = a_index.data();

    if (value.canConvert<bool>()) {
        bool boolVal = value.isValid() ? value.toBool() : defaultValue;

        QStyle *style        = qApp->style();
        QRect   checkBoxRect = style->subElementRect(QStyle::SE_CheckBoxIndicator, &a_option);

        int chkWidth  = checkBoxRect.width();
        int chkHeight = checkBoxRect.height();

        int centerX   = a_option.rect.left() + qMax(a_option.rect.width()  / 2 - chkWidth  / 2, 0);
        int centerY   = a_option.rect.top()  + qMax(a_option.rect.height() / 2 - chkHeight / 2, 0);

        QStyleOptionViewItem modifiedOption(a_option);
        modifiedOption.rect.moveTo(centerX, centerY);
        modifiedOption.rect.setSize(QSize(chkWidth, chkHeight));

        if (boolVal) {
            modifiedOption.state |= QStyle::State_On;
        }

        style->drawPrimitive(QStyle::PE_IndicatorItemViewItemCheck, &modifiedOption, a_painter);
    } else {
        QStyledItemDelegate::paint(a_painter, a_option, a_index);
    }
}
//-------------------------------------------------------------------------------------------------
void
CheckBoxItemDelegate::slot_OnToggled()
{
    qDebug() << __FUNCTION__;
}
