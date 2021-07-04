/* ------------------------------------ Qt ---------------------------------- */
#include <QCoreApplication>
#include <QMessageBox>
/* ----------------------------------- Local -------------------------------- */
#include "project/project_manager.h"
#include "project/new_project_dialog.h"
#include "preferences_manager.h"
/* -------------------------------------------------------------------------- */

QScopedPointer<ProjectManager> ProjectManager::m_instance = QScopedPointer<ProjectManager>(nullptr);

ProjectManager& ProjectManager::getInstance()
{
  if(m_instance.isNull())
    m_instance.reset(new ProjectManager);

  return *m_instance;
}

void ProjectManager::deleteInstance()
{
  m_instance.reset(nullptr);
}

ProjectManager::ProjectManager() = default;

ProjectManager::~ProjectManager() = default;

void ProjectManager::setProject(std::unique_ptr<Project> project)
{
  m_projects = std::move(project);
  Q_EMIT currentProjectChanged(m_projects.get());
}

Project* ProjectManager::getProject() const
{
  return m_projects.get();
}

bool ProjectManager::newProject(Project::Type type)
{
  auto new_project = NewProjectDialog::createProject(type);
  if(new_project && closeProject())
  {
    new_project->save(new_project->getFileName());
    setProject(std::move(new_project));
    return true;
  }

  return false;
}

bool ProjectManager::loadProject(const QString& file_name)
{
  if(m_projects && m_projects->getFileName() == file_name)
    return true;

  auto project = Project::load(file_name);
  if(!project)
  {
    QMessageBox::critical(nullptr,
                          tr("Error Opening File"),
                          tr("Error opening '%1'").arg(file_name));
    return false;
  }

  if(closeProject())
  {
    PreferencesManager::getInstance().addRecentProjectFile(file_name);
    setProject(std::move(project));
    return true;
  }

  return false;
}

bool ProjectManager::closeProject()
{
  if(!m_projects)
    return true;

  auto ret = QMessageBox::question(
    nullptr, tr("Close Project"),
    tr("There is already open project. Are you sure you want to close?"),
    QMessageBox::Yes | QMessageBox::Cancel);

  switch (ret) {
    case QMessageBox::Yes:
      setProject(nullptr);
      return true;
    case QMessageBox::Cancel:
    default:
      return false;
  }
}