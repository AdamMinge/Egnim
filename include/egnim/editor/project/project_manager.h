#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStackedLayout>
#include <QScopedPointer>
#include <QObject>
#include <QTabBar>
#include <QHash>
/* --------------------------------- Standard ------------------------------- */
#include <unordered_map>
#include <memory>
#include <vector>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/project.h>
#include <egnim/editor/project/project_editor.h>
/* -------------------------------------------------------------------------- */

class NoProjectWidget;

class ProjectManager : public QObject
{
  Q_OBJECT

public:
  static ProjectManager& getInstance();
  static void deleteInstance();

public:
  explicit ProjectManager();
  ~ProjectManager() override;

  [[nodiscard]] QWidget *getWidget() const;

  void addEditor(Project::Type project_type, std::unique_ptr<ProjectEditor> editor);
  void removeEditor(Project::Type project_type);
  void removeAllEditors();

  [[nodiscard]] ProjectEditor *getEditor(Project::Type project_type) const;
  [[nodiscard]] ProjectEditor *getCurrentEditor() const;

  void addProject(std::unique_ptr<Project> project);
  void removeProject(int index);
  void removeAllProjects();

  [[nodiscard]] Project *getProject(int index) const;
  [[nodiscard]] Project *getCurrentProject() const;

  [[nodiscard]] int findProject(Project *project) const;

  void switchToProject(int index);
  void switchToProject(Project *project);

  void saveState();
  void restoreState();

  bool saveProject(Project *project);

  [[nodiscard]] const std::vector<std::unique_ptr<Project>> &getProjects() const;

Q_SIGNALS:
  void currentProjectChanged(Project *project);
  void projectCloseRequested(int index);

private Q_SLOTS:
  void currentIndexChanged();
  void projectTabMoved(int from, int to);
  void updateProjectTab(Project *project);

private:
  static QScopedPointer<ProjectManager> m_instance;

  std::vector<std::unique_ptr<Project>> m_projects;
  std::unordered_map<Project::Type, std::unique_ptr<ProjectEditor>> m_editor_for_project_type;

  QScopedPointer<QWidget> m_widget;
  QScopedPointer<NoProjectWidget> m_no_project_widget;
  QTabBar *m_tab_bar;
  QStackedLayout *m_editor_stack;
};

#endif //PROJECT_MANAGER_H
