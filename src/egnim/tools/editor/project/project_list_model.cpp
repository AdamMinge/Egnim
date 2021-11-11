/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/project/project_list_model.h"
#include "egnim/tools/editor/preferences_manager.h"
/* -------------------------------------------------------------------------- */

ProjectListModel::ProjectListModel(QObject* parent) :
  QAbstractListModel(parent)
{
  m_project_type_to_icon.insert(
    std::make_pair(Project::Type::Game, QIcon(":/images/64x64/game_project.png")));
  m_project_type_to_icon.insert(
    std::make_pair(Project::Type::Unknown, QIcon(":/images/64x64/unknown_project.png")));

  connect(std::addressof(PreferencesManager::getInstance()), &PreferencesManager::recentProjectFilesChanged,
          this, &ProjectListModel::recentProjectFilesChanged);

  recentProjectFilesChanged();
}

ProjectListModel::~ProjectListModel() = default;

QVariant ProjectListModel::data(const QModelIndex &index, int role) const
{
  if(index.row() < 0 || index.row() >= m_projects.size())
    return QVariant();

  switch(role) // NOLINT(hicpp-multiway-paths-covered)
  {
    case Role::ProjectNameRole:
      return QFileInfo(m_projects.at(index.row())).baseName();

    case Role::ProjectPathRole:
      return m_projects.at(index.row());

    case Role::ProjectIconRole:
      return getProjectIcon(index);

    case Role::ProjectLastModifiedDateRole:
      return QFileInfo(m_projects.at(index.row())).lastModified();
  }

  return QVariant();
}

int ProjectListModel::rowCount(const QModelIndex &parent) const
{
  return static_cast<int>(m_projects.size());
}

const QIcon& ProjectListModel::getProjectIcon(const QModelIndex& index) const
{
  auto project_file_name = m_projects.at(index.row());
  auto project_extension = QFileInfo(project_file_name).suffix();

  auto project_types = {
    Project::Type::Game
  };

  for(auto project_type : project_types)
    if(project_extension == Project::getProjectExtension(project_type))
      return m_project_type_to_icon.at(project_type);

  return m_project_type_to_icon.at(Project::Type::Unknown);
}

void ProjectListModel::recentProjectFilesChanged()
{
  beginResetModel();
  m_projects = PreferencesManager::getInstance().getRecentProjectFiles();
  endResetModel();
}
