/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/no_editor_widget.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_no_editor_widget.h"
/* -------------------------------------------------------------------------- */

NoEditorWidget::NoEditorWidget(QWidget* parent) :
  QWidget(parent),
  m_ui(new Ui::NoEditorWidget())
{
  m_ui->setupUi(this);
}

NoEditorWidget::~NoEditorWidget() = default;