/* ------------------------------------ Qt ---------------------------------- */
#include <QFileSystemModel>
/* ----------------------------------- Local -------------------------------- */
#include "models//file_system_proxy_model.h"
/* -------------------------------------------------------------------------- */

FileSystemProxyModel::FileSystemProxyModel(QObject* parent) :
  QSortFilterProxyModel(parent)
{

}

FileSystemProxyModel::~FileSystemProxyModel() = default;

bool FileSystemProxyModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{
  auto source_model = dynamic_cast<QFileSystemModel*>(sourceModel());
  if(source_model)
  {
    auto root_path = source_model->rootPath();
    auto root_index = source_model->index(root_path).parent();
    auto source_parent = mapToSource(parent);

    if(root_index == source_parent)
    {
      auto new_parent = mapFromSource(source_model->index(root_path));
      return QSortFilterProxyModel::dropMimeData(data, action, row, column, new_parent);
    }
  }

  return QSortFilterProxyModel::dropMimeData(data, action, row, column, parent);
}

bool FileSystemProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
  auto source_model = dynamic_cast<QFileSystemModel*>(sourceModel());
  if(source_model)
  {
    auto root_path = source_model->rootPath();
    auto root_index = source_model->index(root_path).parent();
    if(root_index == source_parent)
    {
      auto index = source_model->index(source_row, 0, source_parent);
      return index.data(QFileSystemModel::FilePathRole) == root_path;
    }
  }

  return true;
}