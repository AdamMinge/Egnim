#ifndef PROJECT_FILE_SYSTEM_MODEL_H
#define PROJECT_FILE_SYSTEM_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QFileSystemModel>
/* -------------------------------------------------------------------------- */

class ProjectFileSystemModel : public QFileSystemModel
{
public:
  explicit ProjectFileSystemModel(QObject* parent = nullptr);
  ~ProjectFileSystemModel() override;

  bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) override;
};

#endif //PROJECT_FILE_SYSTEM_MODEL_H
