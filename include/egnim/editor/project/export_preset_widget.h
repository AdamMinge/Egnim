#ifndef EXPORT_PRESET_WIDGET_H
#define EXPORT_PRESET_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

class ExportPreset;
class WindowsExportPreset;
class LinuxExportPreset;
class MacOSExportPreset;

namespace Ui { class ExportPresetWidget; }

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

  void setCurrentPreset(ExportPreset* export_preset) override = 0;
  [[nodiscard]] ExportPreset* getCurrentPreset() const override = 0;

protected:
  void changeEvent(QEvent* event) override;

protected:
  QScopedPointer<Ui::ExportPresetWidget> m_ui;

private:
  void retranslateUi();
};

class WindowsExportPresetWidget : public BaseExportPresetWidget
{
  Q_OBJECT

public:
  explicit WindowsExportPresetWidget(QWidget* parent = nullptr);
  ~WindowsExportPresetWidget() override;

  void setCurrentPreset(ExportPreset* export_preset) override;
  [[nodiscard]] ExportPreset* getCurrentPreset() const override;

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
