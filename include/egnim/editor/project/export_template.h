#ifndef EGNIM_EXPORT_TEMPLATE_H
#define EGNIM_EXPORT_TEMPLATE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

class ExportTemplate : public QObject
{
  Q_OBJECT

public:
  static std::unique_ptr<ExportTemplate> load(const QString& path);

public:
  virtual ~ExportTemplate();

protected:
  explicit ExportTemplate();

  bool init(const QString& path);
};

#endif //EGNIM_EXPORT_TEMPLATE_H
