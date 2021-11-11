/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
#include <QDir>
/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/project/export_template.h"
#include "egnim/tools/editor/project/export_preset.h"
#include "egnim/tools/editor/project/project.h"
#include "egnim/tools/editor/utils/zip_file.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<ExportTemplate> ExportTemplate::load(const QString& path)
{
  auto project_export_template = std::unique_ptr<ExportTemplate>(new ExportTemplate);

  if(!QFile::exists(path))                  return nullptr;
  if(!project_export_template->init(path))  return nullptr;

  return project_export_template;
}

ExportTemplate::~ExportTemplate() = default;

ExportTemplate::ExportTemplate() = default;

bool ExportTemplate::init(const QString& path)
{
  m_zip = ZipFile::load(path);
  return static_cast<bool>(m_zip);
}

QString ExportTemplate::getFileName() const
{
  Q_ASSERT(m_zip);
  return m_zip->getFileName();
}

QString ExportTemplate::getDisplayName() const
{
  return QFileInfo(getFileName()).fileName();
}

bool ExportTemplate::canExportTemplate(const ExportPreset& export_preset) const
{
  Q_ASSERT(m_zip);

  const auto entry_name = export_preset.getExportExecutableName();
  return m_zip->hasEntryName(entry_name);
}

bool ExportTemplate::exportTemplate(const ExportPreset& export_preset) const
{
  if(!canExportTemplate(export_preset))
    return false;

  const auto entry_name = export_preset.getExportExecutableName();
  const auto export_path = export_preset.getExportPath();

  return m_zip->extract(entry_name, export_path);
}
