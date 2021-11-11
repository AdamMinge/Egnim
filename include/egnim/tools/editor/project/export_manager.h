#ifndef EGNIM_EXPORT_MANAGER_H
#define EGNIM_EXPORT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/project/export_preset.h"
/* -------------------------------------------------------------------------- */

class ExportTemplateListModel;
class ExportTemplate;
class ExportPreset;
class Project;

class ExportManager : public QObject
{
  Q_OBJECT

public:
  enum class ExportResult;

public:
  static ExportManager& getInstance();
  static void deleteInstance();

public:
  ~ExportManager() override;

  template<typename ...TYPE>
  ExportManager::ExportResult exportProject(const Project& project, TYPE&& ...export_presets) const; // NOLINT(modernize-use-nodiscard)

protected:
  ExportManager::ExportResult exportProjectUsingPreset(const Project& project, const ExportPreset& export_preset) const; // NOLINT(modernize-use-nodiscard)

private:
  explicit ExportManager();

private:
  static QScopedPointer<ExportManager> m_instance;

  ExportTemplateListModel* m_export_template_model;
  ExportTemplate* m_current_export_template;
};

enum class ExportManager::ExportResult
{
  SUCCESS,
  FAIL_MISSING_TEMPLATE,
  FAIL_EXPORT_TEMPLATE,
  FAIL_EXPORT_PROJECT,
};

template<typename ...IsExportPreset>
ExportManager::ExportResult ExportManager::exportProject(
    const Project& project, IsExportPreset&& ...export_presets) const
{
  return (exportProjectUsingPreset(project, std::forward<IsExportPreset>(export_presets)) && ...);
}

#endif //EGNIM_EXPORT_MANAGER_H
