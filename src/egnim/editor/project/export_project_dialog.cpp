/* ------------------------------------ Qt ---------------------------------- */
#include <QMenu>
#include <QMessageBox>
/* ----------------------------------- Local -------------------------------- */
#include "project/project_manager.h"
#include "project/export_preset_widget.h"
#include "project/export_project_dialog.h"
#include "project/export_preset_list_model.h"
#include "project/export_manager.h"
#include "project/project.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_export_project_dialog.h"
/* -------------------------------------------------------------------------- */

static QString exportResultToMessage(ExportManager::ExportResult result)
{
  switch(result)
  {
    case ExportManager::ExportResult::FAIL_MISSING_TEMPLATE:
      return QObject::tr("Error occurred while trying find template");
    case ExportManager::ExportResult::FAIL_EXPORT_PROJECT:
      return QObject::tr("Error occurred while trying export project");
    case ExportManager::ExportResult::FAIL_EXPORT_TEMPLATE:
      return QObject::tr("Error occurred while trying export template");

    default:
      return "";
  }
}

ExportProjectDialog::ExportProjectDialog(QWidget* parent) :
  QDialog(parent),
  m_current_preset(nullptr),
  m_ui(new Ui::ExportProjectDialog()),
  m_export_preset_model(ProjectManager::getInstance().getProject()->getExportPresetModel())
{
  m_ui->setupUi(this);

  Q_ASSERT(m_export_preset_model);
  m_ui->m_presets_list_view->setModel(m_export_preset_model);

  addEditor(ExportPreset::Type::Windows, std::make_unique<WindowsExportPresetWidget>());
  addEditor(ExportPreset::Type::Linux, std::make_unique<LinuxExportPresetWidget>());
  addEditor(ExportPreset::Type::MacOS, std::make_unique<MacOSExportPresetWidget>());
  addEditor(ExportPreset::Type::Unknown, std::make_unique<UnknownExportPresetWidget>());

  m_ui->m_presets_stacked_widget->setCurrentWidget(getEditor(ExportPreset::Type::Unknown));

  connect(m_ui->m_presets_list_view->selectionModel(), &QItemSelectionModel::currentChanged,
          this, &ExportProjectDialog::currentPresetChanged);
  connect(m_export_preset_model, &ExportPresetListModel::rowsInserted,
          this, &ExportProjectDialog::updateActions);
  connect(m_export_preset_model, &ExportPresetListModel::rowsRemoved,
          this, &ExportProjectDialog::updateActions);

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
  updateActions();
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

void ExportProjectDialog::exportWithPresets(const ExportPreset& export_preset)
{
  auto project = ProjectManager::getInstance().getProject();
  Q_ASSERT(project != nullptr);

  auto export_result = ExportManager::getInstance().exportProject(*project, export_preset);
  if(export_result != ExportManager::ExportResult::SUCCESS)
  {
    QMessageBox::critical(this,
                          tr("Error Export Project [ %1 ]").arg(export_preset.getName()),
                          exportResultToMessage(export_result));
  }
}

void ExportProjectDialog::exportWithCurrentPreset()
{
  Q_ASSERT(m_current_preset != nullptr);
  exportWithPresets(*m_current_preset);
}

void ExportProjectDialog::exportWithAllPresets()
{
  auto row_count = m_export_preset_model->rowCount(QModelIndex());
  for(auto row = 0; row < row_count; ++row)
  {
    auto current_preset = m_export_preset_model->getExportPreset(m_export_preset_model->index(row));
    Q_ASSERT(current_preset != nullptr);
    exportWithPresets(*current_preset);
  }
}

void ExportProjectDialog::addPreset(ExportPreset::Type preset_type)
{
  auto project = ProjectManager::getInstance().getProject();
  Q_ASSERT(project != nullptr);

  const auto export_path = QString("%1%2").arg(
      project->getDirectory().filePath(QFileInfo(project->getDisplayName()).baseName()),
      ExportPreset::getExecutableExtension(preset_type));

  switch(preset_type)
  {
    case ExportPreset::Type::Windows:
      m_export_preset_model->appendExportPreset(
        std::make_unique<WindowsExportPreset>(
            tr("Windows"), export_path));
      break;

    case ExportPreset::Type::Linux:
      m_export_preset_model->appendExportPreset(
        std::make_unique<LinuxExportPreset>(
            tr("Linux"), export_path));
      break;

    case ExportPreset::Type::MacOS:
      m_export_preset_model->appendExportPreset(
        std::make_unique<MacOSExportPreset>(
            tr("MacOS"), export_path));
      break;

    case ExportPreset::Type::Unknown:
      break;
  }
}

void ExportProjectDialog::copyPreset()
{
  auto index = m_ui->m_presets_list_view->selectionModel()->currentIndex();
  Q_ASSERT(index.isValid());

  auto export_preset = m_export_preset_model->getExportPreset(index);
  auto copy_export_preset = export_preset->clone();

  copy_export_preset->setName(QString("%1 Copy").arg(copy_export_preset->getName()));
  m_export_preset_model->appendExportPreset(std::move(copy_export_preset));
}

void ExportProjectDialog::removePreset()
{
  auto index = m_ui->m_presets_list_view->selectionModel()->currentIndex();
  Q_ASSERT(index.isValid());
  m_export_preset_model->removeExportPreset(index);
}

void ExportProjectDialog::currentPresetChanged(const QModelIndex& index)
{
  m_current_preset = m_export_preset_model->getExportPreset(index);

  auto current_preset_editor = m_current_preset ? getEditor(m_current_preset->getType()) : nullptr;
  auto editor = current_preset_editor ? current_preset_editor : getEditor(ExportPreset::Type::Unknown);

  m_ui->m_presets_stacked_widget->setCurrentWidget(editor);

  editor->setCurrentPreset(m_current_preset);

  updateActions();
}

void ExportProjectDialog::retranslateUi()
{
  m_ui->retranslateUi(this);
}

void ExportProjectDialog::updateActions()
{
  const auto selected_preset = m_current_preset != nullptr;
  const auto any_preset_on_list = m_export_preset_model->rowCount(QModelIndex()) > 0;

  m_ui->m_export_button->setEnabled(selected_preset);
  m_ui->m_export_all_button->setEnabled(any_preset_on_list);
  m_ui->m_copy_button->setEnabled(selected_preset);
  m_ui->m_remove_button->setEnabled(selected_preset);
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
  auto export_preset_widget = dynamic_cast<ExportPresetWidget*>(m_ui->m_presets_stacked_widget->currentWidget());
  Q_ASSERT(export_preset_widget);

  return export_preset_widget;
}