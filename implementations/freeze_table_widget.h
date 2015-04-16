#ifndef FREEZETABLEWIDGET_H
#define FREEZETABLEWIDGET_H

#include <QTableView>
#include <QHeaderView>
#include <QScrollBar>

class FreezeTableWidget : public QTableView {
  Q_OBJECT

public:
   FreezeTableWidget(QAbstractItemModel *model, QWidget *parentWidget = 0);
   ~FreezeTableWidget();

protected:
   virtual void resizeEvent(QResizeEvent *event);
   virtual QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers);
   void scrollTo (const QModelIndex & index, ScrollHint hint = EnsureVisible);

private:
   QTableView *frozenTableView;
   void init();
   void updateFrozenTableGeometry();

private slots:
   void updateSectionWidth(int logicalIndex,int, int newSize);
   void updateSectionHeight(int logicalIndex, int, int newSize);

};
#endif
