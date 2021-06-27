/* ----------------------------------- Local -------------------------------- */
#include "settings_dialog.h"
#include "language_manager.h"
#include "style_manager.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_settings_dialog.h"
/* -------------------------------------------------------------------------- */

SettingsDialog::SettingsDialog(QWidget* parent) :
  QDialog(parent),
  m_ui(new Ui::SettingsDialog())
{
  m_ui->setupUi(this);

  m_ui->m_language_combo_box->addItems(LanguageManager::getInstance().getAvailableLanguages());
  m_ui->m_style_combo_box->addItems(StyleManager::getInstance().getAvailableStyles());

  connect(m_ui->m_language_combo_box, &QComboBox::currentIndexChanged, this, &SettingsDialog::languageChanged);
  connect(m_ui->m_style_combo_box, &QComboBox::currentIndexChanged, this, &SettingsDialog::styleChanged);

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

void SettingsDialog::languageChanged()
{

}

void SettingsDialog::styleChanged()
{

}

void SettingsDialog::retranslateUi()
{
  m_ui->retranslateUi(this);
}