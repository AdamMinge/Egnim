#ifndef EXPORT_PRESET_WIDGET_H
#define EXPORT_PRESET_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

class ExportPreset;
class WindowsExportPreset;
class LinuxExportPreset;
class MacOSExportPreset;

namespace Ui
{
  class WindowsExportPresetWidget;
  class LinuxExportPresetWidget;
  class MacOSExportPresetWidget;
}

class ExportPresetWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ExportPresetWidget(QWidget* parent = nullptr);
  ~ExportPresetWidget() override;

  virtual void setCurrentPreset(ExportPreset* export_preset) = 0;
  [[nodiscard]] virtual ExportPreset* getCurrentPreset() const = 0;

protected:
  void changeEvent(QEvent* event) override;

private:
  virtual void retranslateUi() = 0;
};

class WindowsExportPresetWidget : public ExportPresetWidget
{
  Q_OBJECT

public:
  explicit WindowsExportPresetWidget(QWidget* parent = nullptr);
  ~WindowsExportPresetWidget() override;

  void setCurrentPreset(ExportPreset* export_preset) override;
  [[nodiscard]] ExportPreset* getCurrentPreset() const override;

private:
  void retranslateUi() override;

private:
  QScopedPointer<Ui::WindowsExportPresetWidget> m_ui;
  WindowsExportPreset* m_export_preset;
};

class LinuxExportPresetWidget : public ExportPresetWidget
{
  Q_OBJECT

public:
  explicit LinuxExportPresetWidget(QWidget* parent = nullptr);
  ~LinuxExportPresetWidget() override;

  void setCurrentPreset(ExportPreset* export_preset) override;
  [[nodiscard]] ExportPreset* getCurrentPreset() const override;

private:
  void retranslateUi() override;

private:
  QScopedPointer<Ui::LinuxExportPresetWidget> m_ui;
  LinuxExportPreset* m_export_preset;
};

class MacOSExportPresetWidget : public ExportPresetWidget
{
  Q_OBJECT

public:
  explicit MacOSExportPresetWidget(QWidget* parent = nullptr);
  ~MacOSExportPresetWidget() override;

  void setCurrentPreset(ExportPreset* export_preset) override;
  [[nodiscard]] ExportPreset* getCurrentPreset() const override;

private:
  void retranslateUi() override;

private:
  QScopedPointer<Ui::MacOSExportPresetWidget> m_ui;
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
  void retranslateUi() override;

private:
  ExportPreset* m_export_preset;
};

#endif //EXPORT_PRESET_WIDGET_H
