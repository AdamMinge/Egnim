/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QMenu>
/* ----------------------------------- Local -------------------------------- */
#include "project/project_dock.h"
#include "project/project_manager.h"
#include "document/document_manager.h"
#include "models/file_system_proxy_model.h"
#include "action_manager.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_project_dock.h"
/* -------------------------------------------------------------------------- */

ProjectDock::ProjectDock(QWidget* parent) :
  QDockWidget(parent),
  m_ui(new Ui::ProjectDock()),
  m_files_model(new QFileSystemModel()),
  m_proxy_model(new FileSystemProxyModel()),
  m_current_project(nullptr)
{
  m_ui->setupUi(this);
  setObjectName(QLatin1String("Project"));

  m_proxy_model->setSourceModel(m_files_model.get());
  m_ui->m_project_files_tree_view->setModel(m_proxy_model.get());
  m_ui->m_project_files_tree_view->setContextMenuPolicy(Qt::CustomContextMenu);

  m_ui->m_project_files_tree_view->setColumnHidden(Column_Size, true);
  m_ui->m_project_files_tree_view->setColumnHidden(Column_Type, true);
  m_ui->m_project_files_tree_view->setColumnHidden(Column_Date_Modified, true);

  m_files_model->setNameFilterDisables(false);

  connect(m_ui->m_search_project_files_edit, &QLineEdit::textChanged, this, &ProjectDock::searchProjectFiles);

  connect(m_ui->m_project_files_tree_view, &QTreeView::doubleClicked, this, &ProjectDock::onDoubleClicked);

  retranslateUi();
}

ProjectDock::~ProjectDock() = default;

void ProjectDock::setCurrentProject(Project* project)
{
  m_current_project = project;

  if(m_current_project)
  {
    auto source_root_index = m_files_model->setRootPath(m_current_project->getDirectory().absolutePath());
    auto root_index = m_proxy_model->mapFromSource(source_root_index);

    m_ui->m_project_files_tree_view->setRootIndex(root_index.parent());
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

void ProjectDock::searchProjectFiles(const QString& search)
{
  auto search_wildcard = QString("*%1*").arg(search);
  m_files_model->setNameFilters(QStringList() << search_wildcard);
}

void ProjectDock::onDoubleClicked(const QModelIndex& index)
{
  auto source_index = m_proxy_model->mapToSource(index);
  auto file_path = source_index.data(QFileSystemModel::FilePathRole).toString();
  auto file_info = QFileInfo(file_path);

  if(file_info.isFile())
  {
    auto document_extensions = Document::getDocumentExtensions();

    if(document_extensions.contains(file_info.suffix()))
      DocumentManager::getInstance().loadDocument(file_path);
  }
}

void ProjectDock::retranslateUi()
{
  m_ui->retranslateUi(this);

  setWindowTitle(tr("Project"));
}

