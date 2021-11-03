/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
#include <QDir>
/* ----------------------------------- Local -------------------------------- */
#include "project/export_template.h"
#include "project/export_preset.h"
#include "project/project.h"
#include "utils/zip_file.h"
/* -------------------------------------------------------------------------- */

static QString ExportToEntryName(const ExportPreset& export_preset)
{
  constexpr auto str_types = std::array{
      std::pair{"windows", ".exe"},
      std::pair{"linux", ""},
      std::pair{"mac", ".app"}
  };

  constexpr auto str_versions = std::array{
      "x32_debug",
      "x32_release",
      "x64_debug",
      "x64_release"
  };

  const auto type = export_preset.getType();
  const auto version = export_preset.getVersion();

  Q_ASSERT(static_cast<int>(type) >= 0 && static_cast<int>(type) < str_types.size());
  Q_ASSERT(static_cast<int>(version) >= 0 && static_cast<int>(version) < str_versions.size());

  return QString("%1_%2%3").arg(
      std::get<0>(str_types[static_cast<int>(type)]),
      str_versions[static_cast<int>(version)],
      std::get<1>(str_types[static_cast<int>(type)]));
}

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

  const auto entry_name = ExportToEntryName(export_preset);
  return m_zip->hasEntryName(entry_name);
}

bool ExportTemplate::exportTemplate(const ExportPreset& export_preset) const
{
  if(!canExportTemplate(export_preset))
    return false;

  const auto entry_name = ExportToEntryName(export_preset);
  const auto export_path = export_preset.getExportPath();

  return m_zip->extract(entry_name, export_path);
}
