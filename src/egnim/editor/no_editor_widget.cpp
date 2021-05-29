/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/no_editor_widget.h>
#include <egnim/editor/action_manager.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_no_editor_widget.h"
/* -------------------------------------------------------------------------- */

NoEditorWidget::NoEditorWidget(QWidget* parent) :
  QWidget(parent),
  m_ui(new Ui::NoEditorWidget())
{
  m_ui->setupUi(this);

  connect(m_ui->m_new_project_button, &QPushButton::pressed, ActionManager::getInstance().findAction("new_project"), &QAction::trigger);
  connect(m_ui->m_open_button, &QPushButton::pressed, ActionManager::getInstance().findAction("open_project"), &QAction::trigger);
}

NoEditorWidget::~NoEditorWidget() = default;