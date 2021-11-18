#ifndef EXPORT_PRESET_WIDGET_H
#define EXPORT_PRESET_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* --------------------------------- Standard ------------------------------- */
#include <map>
/* -------------------------------------------------------------------------- */

class ExportPreset;
class WindowsExportPreset;
class LinuxExportPreset;
class MacOSExportPreset;

namespace Ui { class ExportPresetWidget; }
namespace tools
{
  class QtProperty;

  class QtVariantProperty;
  class QtVariantPropertyManager;
  class QtGroupPropertyManager;
}

class ExportPresetWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ExportPresetWidget(QWidget* parent = nullptr);
  ~ExportPresetWidget() override;

  virtual void setCurrentPreset(ExportPreset* export_preset) = 0;
  [[nodiscard]] virtual ExportPreset* getCurrentPreset() const = 0;
};

class BaseExportPresetWidget : public ExportPresetWidget
{
  Q_OBJECT

public:
  explicit BaseExportPresetWidget(QWidget* parent = nullptr);
  ~BaseExportPresetWidget() override;

  void setCurrentPreset(ExportPreset* export_preset) override;
  [[nodiscard]] ExportPreset* getCurrentPreset() const override = 0;

protected:
  enum class PropertyId;

protected:
  void changeEvent(QEvent* event) override;

  tools::QtVariantProperty* addProperty(
      PropertyId property_id, int type, const QString& name, tools::QtProperty* parent = nullptr);
  tools::QtVariantProperty* addEnumProperty(
      PropertyId property_id, const QStringList& values, const QString& name, tools::QtProperty* parent = nullptr);
  tools::QtProperty* addGroupProperty(
      const QString& name, tools::QtProperty* parent = nullptr);

  virtual void addPlatformProperties();
  virtual void onPlatformPropertyChanged(tools::QtProperty *property, const QVariant &val);

protected:
  QScopedPointer<Ui::ExportPresetWidget> m_ui;

private Q_SLOTS:
  void onBrowsePressed();
  void onPropertyChanged(tools::QtProperty *property, const QVariant &val);

private:
  void retranslateUi();
  void addProperties();

private:
  tools::QtVariantPropertyManager* m_variant_property_manager;
  tools::QtGroupPropertyManager* m_group_property_manager;

  std::map<PropertyId, tools::QtVariantProperty*> m_id_to_property;
  std::map<tools::QtProperty*, PropertyId> m_property_to_id;

  const QStringList m_build_type_names;
  const QStringList m_build_version_names;
};

enum class BaseExportPresetWidget::PropertyId
{
  BuildType,
  BuildVersion,
};

class WindowsExportPresetWidget : public BaseExportPresetWidget
{
  Q_OBJECT

public:
  explicit WindowsExportPresetWidget(QWidget* parent = nullptr);
  ~WindowsExportPresetWidget() override;

  void setCurrentPreset(ExportPreset* export_preset) override;
  [[nodiscard]] ExportPreset* getCurrentPreset() const override;

protected:
  void addPlatformProperties() override;
  void onPlatformPropertyChanged(tools::QtProperty *property, const QVariant &val) override;

private:
  WindowsExportPreset* m_export_preset;
};

class LinuxExportPresetWidget : public BaseExportPresetWidget
{
  Q_OBJECT

public:
  explicit LinuxExportPresetWidget(QWidget* parent = nullptr);
  ~LinuxExportPresetWidget() override;

  void setCurrentPreset(ExportPreset* export_preset) override;
  [[nodiscard]] ExportPreset* getCurrentPreset() const override;

private:
  LinuxExportPreset* m_export_preset;
};

class MacOSExportPresetWidget : public BaseExportPresetWidget
{
  Q_OBJECT

public:
  explicit MacOSExportPresetWidget(QWidget* parent = nullptr);
  ~MacOSExportPresetWidget() override;

  void setCurrentPreset(ExportPreset* export_preset) override;
  [[nodiscard]] ExportPreset* getCurrentPreset() const override;

private:
  MacOSExportPreset* m_export_preset;
};

class UnknownExportPresetWidget : public ExportPresetWidget
{
  Q_OBJECT

public:
  explicit UnknownExportPresetWidget(QWidget* parent = nullptr);
  ~UnknownExportPresetWidget() override;

  void setCurrentPreset(ExportPreset* export_preset) override;
  [[nodiscard]] ExportPreset* getCurrentPreset() const override;

private:
  ExportPreset* m_export_preset;
};

#endif //EXPORT_PRESET_WIDGET_H
