#ifndef EXPORT_PRESET_LIST_MODEL_H
#define EXPORT_PRESET_LIST_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractListModel>
#include <QIcon>
/* ---------------------------------- Standard ------------------------------ */
#include <vector>
/* ----------------------------------- Local -------------------------------- */
#include "project/export_preset.h"
/* -------------------------------------------------------------------------- */

class ExportPresetListModel : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit ExportPresetListModel(QObject* parent = nullptr);
  ~ExportPresetListModel() override;

  [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

  [[nodiscard]] ExportPreset* getExportPreset(const QModelIndex& index) const;
  [[nodiscard]] QModelIndex getIndex(ExportPreset* export_preset) const;

  QModelIndex appendExportPreset(std::unique_ptr<ExportPreset> export_preset);
  QModelIndex prependExportPreset(std::unique_ptr<ExportPreset> export_preset);
  QModelIndex insertExportPreset(const QModelIndex& index, std::unique_ptr<ExportPreset> export_preset);

  void removeExportPreset(const QModelIndex& index);

private Q_SLOTS:
  void nameChanged();

private:
  [[nodiscard]] const QIcon& getProjectIcon(const QModelIndex& index) const;

private:
  std::vector<std::unique_ptr<ExportPreset>> m_export_presets;
  std::map<ExportPreset::Type, QIcon> m_export_preset_type_to_icon;
};

#endif //EXPORT_PRESET_LIST_MODEL_H
