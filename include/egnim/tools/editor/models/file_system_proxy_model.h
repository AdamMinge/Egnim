#ifndef FILE_SYSTEM_PROXY_MODEL_H
#define FILE_SYSTEM_PROXY_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
#include <QFileSystemModel>
/* -------------------------------------------------------------------------- */

class FileSystemProxyModel : public QSortFilterProxyModel
{
  Q_OBJECT

public:
  explicit FileSystemProxyModel(QObject* parent = nullptr);
  ~FileSystemProxyModel() override;

protected:
  [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};


#endif //FILE_SYSTEM_PROXY_MODEL_H
