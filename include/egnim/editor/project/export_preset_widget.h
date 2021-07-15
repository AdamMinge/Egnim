#ifndef EXPORT_PRESET_WIDGET_H
#define EXPORT_PRESET_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

class ExportPresetWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ExportPresetWidget(QWidget* parent = nullptr);
  ~ExportPresetWidget() override;

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

private:
  void retranslateUi() override;
};

class LinuxExportPresetWidget : public ExportPresetWidget
{
  Q_OBJECT

public:
  explicit LinuxExportPresetWidget(QWidget* parent = nullptr);
  ~LinuxExportPresetWidget() override;

private:
  void retranslateUi() override;
};

class MacOSExportPresetWidget : public ExportPresetWidget
{
  Q_OBJECT

public:
  explicit MacOSExportPresetWidget(QWidget* parent = nullptr);
  ~MacOSExportPresetWidget() override;

private:
  void retranslateUi() override;
};


#endif //EXPORT_PRESET_WIDGET_H
