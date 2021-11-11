/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/settings_dialog.h"
#include "egnim/tools/editor/language_manager.h"
#include "egnim/tools/editor/style_manager.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_settings_dialog.h"
/* -------------------------------------------------------------------------- */

SettingsDialog::SettingsDialog(QWidget* parent) :
  QDialog(parent),
  m_ui(new Ui::SettingsDialog())
{
  m_ui->setupUi(this);

  auto languages = LanguageManager::getInstance().getAvailableLanguages();
  auto styles = StyleManager::getInstance().getAvailableStyles();

  for(auto& locale : languages)
    m_ui->m_language_combo_box->addItem(QLocale::languageToString(locale.language()), locale);

  for(auto& style : styles)
    m_ui->m_style_combo_box->addItem(style, style);

  m_ui->m_language_combo_box->setCurrentText(QLocale::languageToString(
    LanguageManager::getInstance().getCurrentLanguage().language()));

  m_ui->m_style_combo_box->setCurrentIndex(m_ui->m_style_combo_box->findData(
    StyleManager::getInstance().getCurrentStyle(), Qt::UserRole, Qt::MatchFlag::MatchContains));

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
  auto locale = m_ui->m_language_combo_box->currentData().value<QLocale>();
  LanguageManager::getInstance().setLanguage(locale);
}

void SettingsDialog::styleChanged()
{
  auto style = m_ui->m_style_combo_box->currentData().value<QString>();
  StyleManager::getInstance().setStyle(style);
}

void SettingsDialog::retranslateUi()
{
  m_ui->retranslateUi(this);
}