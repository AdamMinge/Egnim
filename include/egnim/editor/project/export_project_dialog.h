#ifndef EXPORT_PROJECT_DIALOG_H
#define EXPORT_PROJECT_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* --------------------------------- Standard ------------------------------- */
#include <unordered_map>
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "project/export_preset.h"
/* -------------------------------------------------------------------------- */

namespace Ui { class ExportProjectDialog; }
class ExportPresetWidget;

class ExportProjectDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ExportProjectDialog(QWidget* parent = nullptr);
  ~ExportProjectDialog() override;

protected:
  void changeEvent(QEvent* event) override;

private Q_SLOTS:
  void exportWithCurrentPreset();
  void exportWithAllPresets();

  void addPreset(ExportPreset::Type preset_type);
  void copyPreset();
  void removePreset();

  void currentPresetChanged(const QModelIndex& index);

private:
  void retranslateUi();
  void updateActions();

  void addEditor(ExportPreset::Type preset_type, std::unique_ptr<ExportPresetWidget> editor);
  void removeEditor(ExportPreset::Type preset_type);
  void removeAllEditors();

  [[nodiscard]] ExportPresetWidget* getEditor(ExportPreset::Type preset_type) const;
  [[nodiscard]] ExportPresetWidget* getCurrentEditor() const;

private:
  QScopedPointer<Ui::ExportProjectDialog> m_ui;
  ExportPreset* m_current_preset;
  ExportPresetListModel* m_export_preset_model;
  std::unordered_map<ExportPreset::Type, std::unique_ptr<ExportPresetWidget>> m_preset_editors;
};

#endif //EXPORT_PROJECT_DIALOG_H
