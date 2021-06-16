/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/no_project_widget.h>
#include <egnim/editor/action_manager.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_no_project_widget.h"
/* -------------------------------------------------------------------------- */

NoProjectWidget::NoProjectWidget(QWidget* parent) :
  QWidget(parent),
  m_ui(new Ui::NoProjectWidget())
{
  m_ui->setupUi(this);

  connect(m_ui->m_new_project_button, &QPushButton::pressed, ActionManager::getInstance().findAction("new_game_project"), &QAction::trigger);
  connect(m_ui->m_open_button, &QPushButton::pressed, ActionManager::getInstance().findAction("open_project"), &QAction::trigger);
}

NoProjectWidget::~NoProjectWidget() = default;