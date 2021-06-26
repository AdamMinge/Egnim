/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/settings_dialog.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_settings_dialog.h"
/* -------------------------------------------------------------------------- */

SettingsDialog::SettingsDialog(QWidget* parent) :
  QDialog(parent),
  m_ui(new Ui::SettingsDialog())
{
  m_ui->setupUi(this);

  retranslateUi();
}

SettingsDialog::~SettingsDialog() = default;

void SettingsDialog::changeEvent(QEvent* event)
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

void SettingsDialog::retranslateUi()
{
  m_ui->retranslateUi(this);
}