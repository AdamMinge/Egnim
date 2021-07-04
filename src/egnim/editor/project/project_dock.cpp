/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "project/project_dock.h"
#include "project/project_manager.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_project_dock.h"
/* -------------------------------------------------------------------------- */

ProjectDock::ProjectDock(QWidget* parent) :
  QDockWidget(parent),
  m_ui(new Ui::ProjectDock()),
  m_files_model(new QFileSystemModel),
  m_current_project(nullptr)
{
  m_ui->setupUi(this);
  setObjectName(QLatin1String("Project"));

  m_ui->m_project_content_tree_view->setModel(m_files_model.get());

  m_ui->m_project_content_tree_view->setColumnHidden(Column_Size, true);
  m_ui->m_project_content_tree_view->setColumnHidden(Column_Type, true);
  m_ui->m_project_content_tree_view->setColumnHidden(Column_Date_Modified, true);


  retranslateUi();
}

ProjectDock::~ProjectDock() = default;

void ProjectDock::setCurrentProject(Project* project)
{
  m_current_project = project;

  if(m_current_project)
  {
    auto dir = QFileInfo(m_current_project->getFileName()).absoluteDir();
    auto root_index = m_files_model->setRootPath(dir.absolutePath());
    m_ui->m_project_content_tree_view->setRootIndex(root_index);
  }
}

Project* ProjectDock::getCurrentProject() const
{
  return m_current_project;
}

void ProjectDock::changeEvent(QEvent* event)
{
  QDockWidget::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void ProjectDock::retranslateUi()
{
  m_ui->retranslateUi(this);

  setWindowTitle(tr("Project"));
}

