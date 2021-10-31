#ifndef EGNIM_EXPORT_TEMPLATE_H
#define EGNIM_EXPORT_TEMPLATE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "project/export_preset.h"
/* -------------------------------------------------------------------------- */

class ZipFile;

class ExportTemplate : public QObject
{
  Q_OBJECT

public:
  static std::unique_ptr<ExportTemplate> load(const QString& path);

public:
  ~ExportTemplate() override;

  [[nodiscard]] QString getFileName() const;
  [[nodiscard]] QString getDisplayName() const;

  [[nodiscard]] bool canExportTemplate(ExportPreset::Type type, ExportPreset::Version version);
  bool exportTemplate(ExportPreset::Type type, ExportPreset::Version version, const QString& dir);

protected:
  explicit ExportTemplate();

  bool init(const QString& path);

private:
  std::unique_ptr<ZipFile> m_zip;
};

#endif //EGNIM_EXPORT_TEMPLATE_H
