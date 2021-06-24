/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/about_dialog.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_about_dialog.h"
/* -------------------------------------------------------------------------- */

AboutDialog::AboutDialog(QWidget* parent) :
  QDialog(parent),
  m_ui(new Ui::AboutDialog())
{
  m_ui->setupUi(this);
}

AboutDialog::~AboutDialog() = default;