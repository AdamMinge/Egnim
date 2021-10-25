#ifndef EGNIM_EXPORT_MANAGER_H
#define EGNIM_EXPORT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* -------------------------------------------------------------------------- */

class ExportTemplateListModel;

class ExportManager : public QObject
{
  Q_OBJECT

public:
  static ExportManager& getInstance();
  static void deleteInstance();

public:
  ~ExportManager() override;

private:
  explicit ExportManager();

private:
  static QScopedPointer<ExportManager> m_instance;

  ExportTemplateListModel* m_export_template_model;
};

#endif //EGNIM_EXPORT_MANAGER_H
