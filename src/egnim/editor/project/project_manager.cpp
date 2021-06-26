/* ------------------------------------ Qt ---------------------------------- */
#include <QMessageBox>
#include <QCoreApplication>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/project_manager.h>
#include <egnim/editor/project/no_project_widget.h>
#include <egnim/editor/preferences_manager.h>
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

ProjectManager::ProjectManager() :
  m_widget(new QWidget()),
  m_tab_bar(new QTabBar(m_widget.data())),
  m_editor_stack(new QStackedLayout()),
  m_no_project_widget(new NoProjectWidget()),
  m_undo_group(new QUndoGroup(this))
{
  m_tab_bar->setExpanding(false);
  m_tab_bar->setDocumentMode(true);
  m_tab_bar->setTabsClosable(true);
  m_tab_bar->setMovable(true);
  m_tab_bar->setContextMenuPolicy(Qt::CustomContextMenu);

  auto vertical_layout = new QVBoxLayout(m_widget.data());
  vertical_layout->addWidget(m_tab_bar);
  vertical_layout->setContentsMargins(0, 0, 0, 0);
  vertical_layout->setSpacing(0);
  vertical_layout->addLayout(m_editor_stack);

  m_editor_stack->addWidget(m_no_project_widget.data());

  connect(m_tab_bar, &QTabBar::currentChanged, this, &ProjectManager::currentIndexChanged);
  connect(m_tab_bar, &QTabBar::tabMoved, this, &ProjectManager::projectTabMoved);
  connect(m_tab_bar, &QTabBar::tabCloseRequested, this, &ProjectManager::projectCloseRequested);
}

ProjectManager::~ProjectManager()
{
  removeAllProjects();
  removeAllEditors();
}

QWidget* ProjectManager::getWidget() const
{
  return m_widget.data();
}

void ProjectManager::addEditor(Project::Type project_type, std::unique_ptr<ProjectEditor> editor)
{
  m_editor_stack->addWidget(editor->getEditorWidget());
  m_editor_for_project_type.insert(std::make_pair(project_type, std::move(editor)));
}

void ProjectManager::removeEditor(Project::Type project_type)
{
  Q_ASSERT(m_editor_for_project_type.contains(project_type));
  m_editor_for_project_type.erase(project_type);
}

void ProjectManager::removeAllEditors()
{
  while(!m_editor_for_project_type.empty())
    removeEditor(m_editor_for_project_type.begin()->first);
}

ProjectEditor* ProjectManager::getEditor(Project::Type project_type) const
{
  if(m_editor_for_project_type.contains(project_type))
    return m_editor_for_project_type.at(project_type).get();

  return nullptr;
}

ProjectEditor* ProjectManager::getCurrentEditor() const
{
  auto current_project = getCurrentProject();
  return current_project ? getEditor(current_project->getType()) : nullptr;
}

void ProjectManager::addProject(std::unique_ptr<Project> project)
{
  Q_ASSERT(project);

  auto& project_ref = *project;

  m_projects.emplace_back(std::move(project));
  m_undo_group->addStack(project_ref.getUndoStack());

  auto editor = getEditor(project_ref.getType());
  Q_ASSERT(editor);
  editor->addProject(std::addressof(project_ref));

  auto project_index = m_tab_bar->addTab(project_ref.getDisplayName());
  m_tab_bar->setTabToolTip(project_index, project_ref.getFileName());

  connect(std::addressof(project_ref), &Project::modifiedChanged, this,
          [this, project = std::addressof(project_ref)] { updateProjectTab(project); });
  connect(std::addressof(project_ref), &Project::fileNameChanged, this,
          [this, project = std::addressof(project_ref)] { updateProjectTab(project); });

  switchToProject(project_index);
}

bool ProjectManager::loadProject(const QString& file_name)
{
  if(switchToProject(file_name))
    return true;

  auto project = Project::load(file_name);
  if(!project)
  {
    QMessageBox::critical(m_widget.get(),
                          tr("Error Opening File"),
                          tr("Error opening '%1'").arg(file_name));
    return false;
  }

  PreferencesManager::getInstance().addRecentProjectFile(file_name);
  addProject(std::move(project));
  return true;
}

void ProjectManager::removeProject(int index)
{
  auto project_to_remove = getProject(index);
  Q_ASSERT(project_to_remove);

  auto& editor = m_editor_for_project_type[project_to_remove->getType()];
  Q_ASSERT(editor);
  editor->removeProject(project_to_remove);

  if(getCurrentProject() == project_to_remove)
    editor->setCurrentProject(nullptr);

  auto removed_project_iter = std::remove_if(
    m_projects.begin(), m_projects.end(), [&project_to_remove](auto&& project){
      return project.get() == project_to_remove;
    });

  m_undo_group->removeStack(project_to_remove->getUndoStack());
  m_tab_bar->removeTab(index);

  m_projects.erase(removed_project_iter, m_projects.end());
}

void ProjectManager::removeAllProjects()
{
  while(!m_projects.empty())
    removeProject(m_tab_bar->currentIndex());
}

Project* ProjectManager::getProject(int index) const
{
  if(index < m_projects.size() && index >= 0)
    return m_projects.at(index).get();

  return nullptr;
}

Project* ProjectManager::getCurrentProject() const
{
  auto index = m_tab_bar->currentIndex();
  return getProject(index);
}

int ProjectManager::findProject(Project *project) const
{
  auto found = std::find_if(m_projects.begin(), m_projects.end(), [project](auto& current_project){
    return current_project.get() == project;
  });

  if(found == m_projects.end())
    return -1;

  return static_cast<int>(std::distance(m_projects.begin(), found));
}

void ProjectManager::switchToProject(int index)
{
  m_tab_bar->setCurrentIndex(index);
}

void ProjectManager::switchToProject(Project* project)
{
  auto found_iter = std::find_if(m_projects.begin(), m_projects.end(), [&project](auto&& current_project){
    return current_project.get() == project;
  });

  Q_ASSERT(found_iter != m_projects.end());
  auto index = std::distance(m_projects.begin(), found_iter);
  switchToProject(static_cast<int>(index));
}

bool ProjectManager::switchToProject(const QString& file_name)
{
  auto found_iter = std::find_if(m_projects.begin(), m_projects.end(), [&file_name](auto&& current_project){
    return current_project->getFileName() == file_name;
  });

  if(found_iter == m_projects.end())
    return false;

  auto index = std::distance(m_projects.begin(), found_iter);
  switchToProject(static_cast<int>(index));
  return true;
}

QUndoGroup* ProjectManager::getUndoGroup() const
{
  return m_undo_group;
}

void ProjectManager::saveState()
{
  for(auto& [project_type, editor] : m_editor_for_project_type)
    editor->saveState();
}

void ProjectManager::restoreState()
{
  for(auto& [project_type, editor] : m_editor_for_project_type)
    editor->restoreState();
}

bool ProjectManager::saveProject(Project* project)
{
  Q_ASSERT(project);

  if(!project->save(project->getFileName()))
  {
    switchToProject(project);
    QMessageBox::critical(
      m_widget->window(),
      QCoreApplication::translate("Egnim-ProjectEditor::ProjectManager",
                                  "Error Saving File"), "Something went wrong");
    return false;
  }

  PreferencesManager::getInstance().addRecentProjectFile(project->getFileName());
  return true;
}

const std::vector<std::unique_ptr<Project>>& ProjectManager::getProjects() const
{
  return m_projects;
}

void ProjectManager::currentIndexChanged()
{
  auto project = getCurrentProject();
  auto editor = getCurrentEditor();

  if(project)
    m_undo_group->setActiveStack(project->getUndoStack());

  if(editor)
  {
    editor->setCurrentProject(project);
    m_editor_stack->setCurrentWidget(editor->getEditorWidget());
  }
  else
  {
    m_editor_stack->setCurrentWidget(m_no_project_widget.data());
  }

  Q_EMIT currentProjectChanged(project);
}

void ProjectManager::projectTabMoved(int from, int to)
{
  if(from > to)
    std::rotate(m_projects.rend() - from - 1,
                m_projects.rend() - from,
                m_projects.rend() - to);
  else
    std::rotate(m_projects.begin() + from,
                m_projects.begin() + from + 1,
                m_projects.begin() + to + 1);
}

void ProjectManager::updateProjectTab(Project* project)
{
  const int index = findProject(project);
  if (index == -1)
    return;

  QString tabText = project->getDisplayName();
  if (project->isModified())
    tabText.prepend(QLatin1Char('*'));

  m_tab_bar->setTabText(index, tabText);
  m_tab_bar->setTabToolTip(index, project->getFileName());
}



