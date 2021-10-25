/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
/* ----------------------------------- Local -------------------------------- */
#include "project/export_template.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<ExportTemplate> ExportTemplate::load(const QString& path)
{
  if(!QFile::exists(path))
    return nullptr;

  auto project_export_template = std::unique_ptr<ExportTemplate>(new ExportTemplate);
  project_export_template->init(path);

  return project_export_template;
}

ExportTemplate::~ExportTemplate() = default;

ExportTemplate::ExportTemplate() = default;

bool ExportTemplate::init(const QString& path)
{
  // TODO : implementation //
  return true;
}