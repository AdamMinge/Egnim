#ifndef PROJECT_FILE_SYSTEM_PROXY_MODEL_H
#define PROJECT_FILE_SYSTEM_PROXY_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
#include <QFileSystemModel>
/* -------------------------------------------------------------------------- */

class ProjectFileSystemProxyModel : public QSortFilterProxyModel
{
  Q_OBJECT

public:
  explicit ProjectFileSystemProxyModel(QObject* parent = nullptr);
  ~ProjectFileSystemProxyModel() override;

protected:
  [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};


#endif //PROJECT_FILE_SYSTEM_PROXY_MODEL_H
