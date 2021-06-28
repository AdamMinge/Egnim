/* ----------------------------------- Local -------------------------------- */
#include "project/project_manager.h"
#include "project/no_project_widget.h"
#include "project/project_list_model.h"
#include "project/project_list_delegate.h"
#include "action_manager.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_no_project_widget.h"
/* -------------------------------------------------------------------------- */

NoProjectWidget::NoProjectWidget(QWidget* parent) :
  QWidget(parent),
  m_ui(new Ui::NoProjectWidget()),
  m_projects_model(new ProjectListModel()),
  m_projects_delegate(new ProjectListDelegate()),
  m_search_proxy_model(new QSortFilterProxyModel())
{
  m_ui->setupUi(this);

  connect(m_ui->m_new_project_button, &QPushButton::pressed, ActionManager::getInstance().findAction("new_project"), &QAction::trigger);
  connect(m_ui->m_open_button, &QPushButton::pressed, ActionManager::getInstance().findAction("open_project"), &QAction::trigger);
  connect(m_ui->m_projects_list_view, &QListView::doubleClicked, this, &NoProjectWidget::openProject);
  connect(m_ui->m_search_project_edit, &QLineEdit::textChanged, this, &NoProjectWidget::searchProject);

  m_search_proxy_model->setSourceModel(m_projects_model.get());
  m_ui->m_projects_list_view->setModel(m_search_proxy_model.get());
  m_ui->m_projects_list_view->setItemDelegate(m_projects_delegate.get());

  m_projects_delegate->setIconSize(QSize(64, 64));
  m_projects_delegate->setMargins(QMargins(10, 5, 10, 5));
  m_projects_delegate->setSpacing(10, 15);

  m_search_proxy_model->setFilterRole(ProjectListModel::Role::ProjectNameRole);

  retranslateUi();
}

NoProjectWidget::~NoProjectWidget() = default;

void NoProjectWidget::changeEvent(QEvent* event)
{
  QWidget::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void NoProjectWidget::openProject(const QModelIndex& index)
{
  auto project_path = index.data(ProjectListModel::Role::ProjectPathRole).toString();
  ProjectManager::getInstance().loadProject(project_path);
}

void NoProjectWidget::searchProject(const QString& search)
{
  m_search_proxy_model->setFilterWildcard(search);
}

void NoProjectWidget::retranslateUi()
{
  m_ui->retranslateUi(this);
}