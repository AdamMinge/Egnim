#ifndef EGNIM_EXPORT_TEMPLATE_H
#define EGNIM_EXPORT_TEMPLATE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

class Project;
class ExportPreset;
namespace tools { class QtZipFile; }

class ExportTemplate : public QObject
{
  Q_OBJECT

public:
  static std::unique_ptr<ExportTemplate> load(const QString& path);

public:
  ~ExportTemplate() override;

  [[nodiscard]] QString getFileName() const;
  [[nodiscard]] QString getDisplayName() const;

  [[nodiscard]] bool canExportTemplate(const ExportPreset& export_preset) const;
  bool exportTemplate(const ExportPreset& export_preset) const; // NOLINT(modernize-use-nodiscard)

protected:
  explicit ExportTemplate();

  bool init(const QString& path);

private:
  std::unique_ptr<tools::QtZipFile> m_zip;
};

#endif //EGNIM_EXPORT_TEMPLATE_H
