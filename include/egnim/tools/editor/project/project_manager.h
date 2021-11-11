#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QScopedPointer>
#include <QObject>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/project/project.h"
/* -------------------------------------------------------------------------- */

class ProjectManager : public QObject
{
  Q_OBJECT

public:
  static ProjectManager& getInstance();
  static void deleteInstance();

public:
  ~ProjectManager() override;

  void setProject(std::unique_ptr<Project> project);
  [[nodiscard]] Project *getProject() const;

  bool newProject(Project::Type type);
  bool loadProject(const QString& file_name);
  bool closeProject();

Q_SIGNALS:
  void currentProjectChanged(Project* project);

protected:
  explicit ProjectManager();

private:
  static QScopedPointer<ProjectManager> m_instance;

  std::unique_ptr<Project> m_projects;
};

#endif //PROJECT_MANAGER_H
