#ifndef FILE_SYSTEM_MODEL_H
#define FILE_SYSTEM_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QFileSystemModel>
/* -------------------------------------------------------------------------- */

class FileSystemModel : public QFileSystemModel
{
public:
  explicit FileSystemModel(QObject* parent = nullptr);
  ~FileSystemModel() override;

  bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) override;
};

#endif //FILE_SYSTEM_MODEL_H
