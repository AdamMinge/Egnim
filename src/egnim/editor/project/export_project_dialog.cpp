/* ------------------------------------ Qt ---------------------------------- */
#include <QMenu>
/* ----------------------------------- Local -------------------------------- */
#include "project/export_project_dialog.h"
#include "project/export_preset_widget.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_export_project_dialog.h"
/* -------------------------------------------------------------------------- */

ExportProjectDialog::ExportProjectDialog(QWidget* parent) :
  QDialog(parent),
  m_ui(new Ui::ExportProjectDialog())
{
  m_ui->setupUi(this);

  addEditor(ExportPreset::Type::Windows, std::make_unique<WindowsExportPresetWidget>());
  addEditor(ExportPreset::Type::Linux, std::make_unique<LinuxExportPresetWidget>());
  addEditor(ExportPreset::Type::MacOS, std::make_unique<MacOSExportPresetWidget>());

  connect(m_ui->m_cancel_button, &QPushButton::pressed, this, &QDialog::close);
  connect(m_ui->m_export_button, &QPushButton::pressed, this, &ExportProjectDialog::exportWithCurrentPreset);
  connect(m_ui->m_export_all_button, &QPushButton::pressed, this, &ExportProjectDialog::exportWithAllPresets);

  auto menu = new QMenu();
  m_ui->m_add_button->setMenu(menu);

  menu->addAction(QIcon(":/images/64x64/windows.png"), QLatin1String("Windows"),
                  [this](){ addPreset(ExportPreset::Type::Windows); });
  menu->addAction(QIcon(":/images/64x64/linux.png"), QLatin1String("Linux"),
                  [this](){ addPreset(ExportPreset::Type::Linux); });
  menu->addAction(QIcon(":/images/64x64/macos.png"), QLatin1String("MacOS"),
                  [this](){ addPreset(ExportPreset::Type::MacOS); });

  connect(m_ui->m_copy_button, &QToolButton::pressed, this, &ExportProjectDialog::copyPreset);
  connect(m_ui->m_remove_button, &QToolButton::pressed, this, &ExportProjectDialog::removePreset);

  retranslateUi();
}

ExportProjectDialog::~ExportProjectDialog()
{
  removeAllEditors();
}

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

void ExportProjectDialog::exportWithCurrentPreset()
{

}

void ExportProjectDialog::exportWithAllPresets()
{

}

void ExportProjectDialog::addPreset(ExportPreset::Type preset_type)
{

}

void ExportProjectDialog::copyPreset()
{

}

void ExportProjectDialog::removePreset()
{

}

void ExportProjectDialog::retranslateUi()
{
  m_ui->retranslateUi(this);
}

void ExportProjectDialog::addEditor(ExportPreset::Type preset_type, std::unique_ptr<ExportPresetWidget> editor)
{
  Q_ASSERT(editor);
  m_ui->m_presets_stacked_widget->addWidget(editor.get());
  m_preset_editors.insert(std::make_pair(preset_type, std::move(editor)));
}

void ExportProjectDialog::removeEditor(ExportPreset::Type preset_type)
{
  Q_ASSERT(m_preset_editors.contains(preset_type));
  auto editor = getEditor(preset_type);

  Q_ASSERT(editor);
  m_ui->m_presets_stacked_widget->removeWidget(editor);
  m_preset_editors.erase(preset_type);
}

void ExportProjectDialog::removeAllEditors()
{
  while(!m_preset_editors.empty())
    removeEditor(m_preset_editors.begin()->first);
}

ExportPresetWidget* ExportProjectDialog::getEditor(ExportPreset::Type preset_type) const
{
  if(m_preset_editors.contains(preset_type))
    return m_preset_editors.at(preset_type).get();

  return nullptr;
}

ExportPresetWidget* ExportProjectDialog::getCurrentEditor() const
{
  // TODO implementation
  return nullptr;
}