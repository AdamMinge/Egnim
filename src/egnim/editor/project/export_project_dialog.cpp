/* ----------------------------------- Local -------------------------------- */
#include "project/export_project_dialog.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_export_project_dialog.h"
/* -------------------------------------------------------------------------- */

ExportProjectDialog::ExportProjectDialog(QWidget* parent) :
  QDialog(parent),
  m_ui(new Ui::ExportProjectDialog())
{
  m_ui->setupUi(this);

  retranslateUi();
}

ExportProjectDialog::~ExportProjectDialog() = default;

void ExportProjectDialog::changeEvent(QEvent* event)
{
  QDialog::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void ExportProjectDialog::retranslateUi()
{
  m_ui->retranslateUi(this);
}