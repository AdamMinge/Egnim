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
}

SettingsDialog::~SettingsDialog() = default;