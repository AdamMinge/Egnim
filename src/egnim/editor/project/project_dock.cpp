/* ------------------------------------ Qt ---------------------------------- */
#include <QDesktopServices>
#include <QMessageBox>
#include <QEvent>
#include <QMenu>
#include <QUrl>
/* ----------------------------------- Local -------------------------------- */
#include "project/project_dock.h"
#include "project/project_manager.h"
#include "project/new_directory_dialog.h"
#include "project/rename_file_dialog.h"
#include "project/rename_directory_dialog.h"
#include "document/document_manager.h"
#include "document/new_document_dialog.h"
#include "models/file_system_proxy_model.h"
#include "action_manager.h"
#include "utils.h"
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

  m_ui->m_project_files_tree_view->setColumnHidden(Column_Size, true);
  m_ui->m_project_files_tree_view->setColumnHidden(Column_Type, true);
  m_ui->m_project_files_tree_view->setColumnHidden(Column_Date_Modified, true);

  m_ui->m_project_files_tree_view->setDragEnabled(true);
  m_ui->m_project_files_tree_view->setAcceptDrops(true);
  m_ui->m_project_files_tree_view->setDropIndicatorShown(true);
  m_ui->m_project_files_tree_view->setDragDropMode(QAbstractItemView::InternalMove);
  m_ui->m_project_files_tree_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
  m_ui->m_project_files_tree_view->setContextMenuPolicy(Qt::CustomContextMenu);

  m_proxy_model->setRecursiveFilteringEnabled(true);
  m_proxy_model->setFilterRole(QFileSystemModel::FileNameRole);

  m_files_model->setNameFilterDisables(false);
  m_files_model->setReadOnly(false);
  m_files_model->setNameFilters(utils::projectSupportedFormats());

  connect(m_ui->m_search_project_files_edit, &QLineEdit::textChanged, this, &ProjectDock::searchProjectFiles);

  connect(m_ui->m_project_files_tree_view, &QTreeView::activated, this, &ProjectDock::openProjectFile);
  connect(m_ui->m_project_files_tree_view, &QTreeView::customContextMenuRequested, this, &ProjectDock::onContextMenu);

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

void ProjectDock::newDocument(Document::Type type)
{
  auto new_document = NewDocumentDialog::createDocument(type, getCurrentDirectory());
  if(new_document)
  {
    new_document->save(new_document->getFileName());
    DocumentManager::getInstance().addDocument(std::move(new_document));
  }
}

void ProjectDock::newDirectory()
{
  NewDirectoryDialog new_directory_dialog(getCurrentDirectory());
  new_directory_dialog.create();
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

void ProjectDock::onContextMenu(const QPoint& pos)
{
  const auto index = m_ui->m_project_files_tree_view->indexAt(pos);
  const auto file_path = index.data(QFileSystemModel::FilePathRole).toString();
  const auto directory_index = QFileInfo(file_path).isFile() ? index.parent() : index;

  QMenu menu;
  QMenu new_menu(tr("&New"));
  QMenu refactor_menu(tr("&Refactor"));
  QMenu open_in_menu(tr("&Open In"));

  new_menu.addAction(ActionManager::getInstance().findAction("new_scene_document"));
  new_menu.addSeparator();
  new_menu.addAction(tr("&Directory"), [this](){ newDirectory(); });

  if(index.isValid())
  {
    auto source_root_index = m_files_model->setRootPath(m_current_project->getDirectory().absolutePath());
    auto root_index = m_proxy_model->mapFromSource(source_root_index);

    if(index != root_index)
    {
      refactor_menu.addAction(tr("&Rename"), [this, index](){ rename(index); });
      refactor_menu.addSeparator();
      refactor_menu.addAction(tr("&Delete"), [this, index](){ remove(index); });
    }

    open_in_menu.addAction(tr("&Files"), [this, directory_index](){ open(directory_index); });

    if(QFileInfo(file_path).isFile())
      open_in_menu.addAction(tr("&System Editor"), [this, index](){ open(index); });
  }

  if(!new_menu.isEmpty())       menu.addMenu(&new_menu);
  menu.addSeparator();
  if(!refactor_menu.isEmpty())  menu.addMenu(&refactor_menu);
  menu.addSeparator();
  if(!open_in_menu.isEmpty())   menu.addMenu(&open_in_menu);

  menu.exec(m_ui->m_project_files_tree_view->mapToGlobal(pos));
}

void ProjectDock::searchProjectFiles(const QString& search)
{
  m_proxy_model->setFilterWildcard(search);
}

void ProjectDock::openProjectFile(const QModelIndex& index)
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

void ProjectDock::open(const QModelIndex& index)
{
  Q_ASSERT(index.isValid());
  QDesktopServices::openUrl(QUrl::fromLocalFile(
    index.data(QFileSystemModel::FilePathRole).toString()));
}

void ProjectDock::remove(const QModelIndex& index)
{
  const auto path = index.data(QFileSystemModel::FilePathRole).toString();
  const auto is_file = QFileInfo(path).isFile();

  if(is_file)
  {
    auto ret = QMessageBox::question(
      this, tr("Delete File"),
      tr("Are you sure that you want to permanently delete this file?"),
      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (ret == QMessageBox::Yes)
    {
      if(!QFile(path).remove())
        QMessageBox::information(this, tr("Delete File"),
                                 tr("Failed to delete the file!"));
    }
  }
  else
  {
    auto ret = QMessageBox::question(
      this, tr("Delete Directory"),
      tr("Are you sure that you want to permanently delete this directory and all its contents?"),
      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (ret == QMessageBox::Yes)
    {
      if(!QDir(path).removeRecursively())
        QMessageBox::information(this, tr("Delete Directory"),
                                 tr("Failed to delete the directory!"));
    }
  }
}

void ProjectDock::rename(const QModelIndex& index)
{
  Q_ASSERT(index.isValid());
  const auto path = index.data(QFileSystemModel::FilePathRole).toString();

  if(QFileInfo(path).isFile())
  {
    RenameFileDialog rename_file_dialog(path);
    rename_file_dialog.rename();
  }
  else
  {
    RenameDirectoryDialog rename_directory_dialog(path);
    rename_directory_dialog.rename();
  }
}

void ProjectDock::retranslateUi()
{
  m_ui->retranslateUi(this);

  setWindowTitle(tr("Project"));
}

QString ProjectDock::getCurrentDirectory() const
{
  auto selected_indexes = m_ui->m_project_files_tree_view->selectionModel()->selectedRows();
  auto dir_path = m_current_project->getDirectory().absolutePath();

  if(selected_indexes.size() == 1)
  {
    auto index = selected_indexes.front();
    Q_ASSERT(index.isValid());

    const auto file_path = index.data(QFileSystemModel::FilePathRole).toString();
    const auto directory_index = QFileInfo(file_path).isFile() ? index.parent() : index;
    dir_path = directory_index.data(QFileSystemModel::FilePathRole).toString();
  }

  return dir_path;
}

