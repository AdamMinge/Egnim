#ifndef FILE_SYSTEM_PROXY_MODEL_H
#define FILE_SYSTEM_PROXY_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* -------------------------------------------------------------------------- */

class FileSystemProxyModel : public QSortFilterProxyModel
{
  Q_OBJECT

public:
  explicit FileSystemProxyModel(QObject* parent = nullptr);
  ~FileSystemProxyModel() override;

  bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) override;

  void setSourceModel(QAbstractItemModel* model) override;

protected:
  [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif //FILE_SYSTEM_PROXY_MODEL_H
