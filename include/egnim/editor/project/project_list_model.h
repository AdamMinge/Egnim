#ifndef PROJECT_LIST_MODEL_H
#define PROJECT_LIST_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractListModel>
#include <QStringList>
#include <QIcon>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/project.h>
/* -------------------------------------------------------------------------- */

class ProjectListModel : public QAbstractListModel
{
  Q_OBJECT

public:
  enum Role
  {
    ProjectNameRole = Qt::UserRole + 1,
    ProjectPathRole,
    ProjectIconRole,
    ProjectLastModifiedDateRole,
  };

public:
  explicit ProjectListModel(QObject* parent = nullptr);
  ~ProjectListModel() override;

  [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

private:
  [[nodiscard]] const QIcon& getProjectIcon(const QModelIndex& index) const;

private Q_SLOTS:
  void recentProjectFilesChanged();

private:
  QStringList m_projects;
  std::map<Project::Type, QIcon> m_project_type_to_icon;
};

#endif //PROJECT_LIST_MODEL_H
