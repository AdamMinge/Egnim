/* ----------------------------------- Local -------------------------------- */
#include "project/project.h"
#include "project/export_manager.h"
#include "project/export_template_list_model.h"
/* -------------------------------------------------------------------------- */

QScopedPointer<ExportManager> ExportManager::m_instance = QScopedPointer<ExportManager>(nullptr);

ExportManager& ExportManager::getInstance()
{
  if(m_instance.isNull())
    m_instance.reset(new ExportManager);

  return *m_instance;
}

void ExportManager::deleteInstance()
{
  m_instance.reset(nullptr);
}

ExportManager::ExportManager() :
  m_export_template_model(new ExportTemplateListModel(this)),
  m_current_export_template(nullptr)
{
  /// TO REMOVE
  auto temp = ExportTemplate::load("exec.zip");
  m_export_template_model->appendExportTemplate(std::move(temp));
  m_current_export_template = m_export_template_model->getExportTemplate(m_export_template_model->index(0));
}

ExportManager::~ExportManager() = default;

ExportManager::ExportResult ExportManager::exportProjectUsingPreset(
    const Project& project, const ExportPreset& export_preset) const
{
  if(!m_current_export_template)
    return ExportResult::FAIL_MISSING_TEMPLATE;
  if(!m_current_export_template->exportTemplate(export_preset))
    return ExportResult::FAIL_EXPORT_TEMPLATE;
  if(!export_preset.exportProject(project))
    return ExportResult::FAIL_EXPORT_PROJECT;

  return ExportResult::SUCCESS;
}
