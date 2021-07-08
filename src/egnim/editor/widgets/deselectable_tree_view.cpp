/* ------------------------------------ Qt ---------------------------------- */
#include <QMouseEvent>
/* ---------------------------------- Local --------------------------------- */
#include "widgets/deselectable_tree_view.h"
/* -------------------------------------------------------------------------- */

DeselectableTreeView::DeselectableTreeView(QWidget *parent) :
  QTreeView(parent)
{

}

DeselectableTreeView::~DeselectableTreeView() = default;

void DeselectableTreeView::mousePressEvent(QMouseEvent *event)
{
  if(event->buttons() == Qt::LeftButton)
  {
    auto item = indexAt(event->pos());
    auto selected = selectionModel()->isSelected(indexAt(event->pos()));
    QTreeView::mousePressEvent(event);

    if ((item.row() == -1 && item.column() == -1) || selected)
    {
      clearSelection();
      selectionModel()->setCurrentIndex(QModelIndex(), QItemSelectionModel::Select);
    }
  }
}
