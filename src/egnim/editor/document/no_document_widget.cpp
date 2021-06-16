/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document/no_document_widget.h>
#include <egnim/editor/action_manager.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "document/ui_no_document_widget.h"
/* -------------------------------------------------------------------------- */

NoDocumentWidget::NoDocumentWidget(QWidget* parent) :
  QWidget(parent),
  m_ui(new Ui::NoDocumentWidget())
{
  m_ui->setupUi(this);
}

NoDocumentWidget::~NoDocumentWidget() = default;