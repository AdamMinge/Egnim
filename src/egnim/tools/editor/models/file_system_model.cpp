/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/models/file_system_model.h"
/* -------------------------------------------------------------------------- */

FileSystemModel::FileSystemModel(QObject* parent) :
    QFileSystemModel(parent)
{

}

FileSystemModel::~FileSystemModel() = default;

bool FileSystemModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{
  auto root_path = rootPath();
  auto root_index = index(root_path).parent();

  if(root_index == parent)
  {
    auto new_parent = index(root_path);
    return QFileSystemModel::dropMimeData(data, action, row, column, new_parent);
  }

  return QFileSystemModel::dropMimeData(data, action, row, column, parent);
}