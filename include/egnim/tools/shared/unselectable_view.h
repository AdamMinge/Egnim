#ifndef UNSELECTABLE_VIEW_H
#define UNSELECTABLE_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemView>
#include <QTreeView>
#include <QTableView>
#include <QListView>
#include <QMouseEvent>
/* --------------------------------- Standard ------------------------------- */
#include <concepts>
/* -------------------------------------------------------------------------- */

template<typename VIEW>
requires std::derived_from<VIEW, QAbstractItemView>
class [[maybe_unused]] QUnselectableView : public VIEW
{
public:
  explicit QUnselectableView(QWidget *parent = nullptr);
  ~QUnselectableView() override;

private:
  void mousePressEvent(QMouseEvent *event) override;
};

template<typename VIEW>
requires std::derived_from<VIEW, QAbstractItemView>
QUnselectableView<VIEW>::QUnselectableView(QWidget *parent) :
    VIEW(parent)
{

}

template<typename VIEW>
requires std::derived_from<VIEW, QAbstractItemView>
QUnselectableView<VIEW>::~QUnselectableView() = default;

template<typename VIEW>
requires std::derived_from<VIEW, QAbstractItemView>
void QUnselectableView<VIEW>::mousePressEvent(QMouseEvent *event)
{
  auto item = VIEW::indexAt(event->pos());
  auto selected = VIEW::selectionModel()->isSelected(VIEW::indexAt(event->pos()));

  if ((item.row() == -1 && item.column() == -1) || selected)
  {
    VIEW::clearSelection();
    VIEW::selectionModel()->setCurrentIndex(QModelIndex(), QItemSelectionModel::Select);
  }

  VIEW::mousePressEvent(event);
}

using QUnselectableTreeView = QUnselectableView<QTreeView>;
using QUnselectableListView = QUnselectableView<QListView>;
using QUnselectableTableView = QUnselectableView<QTableView>;

#endif //UNSELECTABLE_VIEW_H
