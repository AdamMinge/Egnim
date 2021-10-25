#ifndef EGNIM_EXPORT_TEMPLATE_LIST_MODEL_H
#define EGNIM_EXPORT_TEMPLATE_LIST_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractListModel>
/* ---------------------------------- Standard ------------------------------ */
#include <vector>
/* ----------------------------------- Local -------------------------------- */
#include "project/export_template.h"
/* -------------------------------------------------------------------------- */

class ExportTemplateListModel : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit ExportTemplateListModel(QObject* parent = nullptr);
  ~ExportTemplateListModel() override;

  [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

  [[nodiscard]] ExportTemplate* getExportTemplate(const QModelIndex& index) const;
  [[nodiscard]] QModelIndex getIndex(ExportTemplate* export_template) const;

  QModelIndex appendExportTemplate(std::unique_ptr<ExportTemplate> export_template);
  QModelIndex prependExportTemplate(std::unique_ptr<ExportTemplate> export_template);
  QModelIndex insertExportTemplate(const QModelIndex& index, std::unique_ptr<ExportTemplate> export_template);

  void removeExportTemplate(const QModelIndex& index);

private:
  std::vector<std::unique_ptr<ExportTemplate>> m_export_templates;
};

#endif //EGNIM_EXPORT_TEMPLATE_LIST_MODEL_H
