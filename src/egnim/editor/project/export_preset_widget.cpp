/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "project/export_preset_widget.h"
#include "project/export_preset.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_windows_export_preset_widget.h"
#include "project/ui_linux_export_preset_widget.h"
#include "project/ui_macos_export_preset_widget.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- ExportPresetWidget ------------------------- */

ExportPresetWidget::ExportPresetWidget(QWidget* parent) :
  QWidget(parent)
{

}

ExportPresetWidget::~ExportPresetWidget() = default;

void ExportPresetWidget::changeEvent(QEvent* event)
{
  QWidget::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

/* ------------------------- WindowsExportPresetWidget ---------------------- */

WindowsExportPresetWidget::WindowsExportPresetWidget(QWidget* parent) :
  ExportPresetWidget(parent),
  m_export_preset(nullptr),
  m_ui(new Ui::WindowsExportPresetWidget())
{
  m_ui->setupUi(this);
}

WindowsExportPresetWidget::~WindowsExportPresetWidget() = default;

void WindowsExportPresetWidget::retranslateUi()
{
  m_ui->retranslateUi(this);
}

void WindowsExportPresetWidget::setCurrentPreset(ExportPreset* export_preset)
{
  auto current_export_preset = dynamic_cast<WindowsExportPreset*>(export_preset);
  Q_ASSERT(current_export_preset || !export_preset);

  m_export_preset = current_export_preset;
}

ExportPreset* WindowsExportPresetWidget::getCurrentPreset() const
{
  return m_export_preset;
}

/* -------------------------- LinuxExportPresetWidget ----------------------- */

LinuxExportPresetWidget::LinuxExportPresetWidget(QWidget* parent) :
  ExportPresetWidget(parent),
  m_export_preset(nullptr),
  m_ui(new Ui::LinuxExportPresetWidget())
{
  m_ui->setupUi(this);
}

LinuxExportPresetWidget::~LinuxExportPresetWidget() = default;

void LinuxExportPresetWidget::retranslateUi()
{
  m_ui->retranslateUi(this);
}

void LinuxExportPresetWidget::setCurrentPreset(ExportPreset* export_preset)
{
  auto current_export_preset = dynamic_cast<LinuxExportPreset*>(export_preset);
  Q_ASSERT(current_export_preset || !export_preset);

  m_export_preset = current_export_preset;
}

ExportPreset* LinuxExportPresetWidget::getCurrentPreset() const
{
  return m_export_preset;
}

/* --------------------------- MacOSExportPresetWidget ---------------------- */

MacOSExportPresetWidget::MacOSExportPresetWidget(QWidget* parent) :
  ExportPresetWidget(parent),
  m_export_preset(nullptr),
  m_ui(new Ui::MacOSExportPresetWidget())
{
  m_ui->setupUi(this);
}

MacOSExportPresetWidget::~MacOSExportPresetWidget() = default;

void MacOSExportPresetWidget::retranslateUi()
{
  m_ui->retranslateUi(this);
}

void MacOSExportPresetWidget::setCurrentPreset(ExportPreset* export_preset)
{
  auto current_export_preset = dynamic_cast<MacOSExportPreset*>(export_preset);
  Q_ASSERT(current_export_preset || !export_preset);

  m_export_preset = current_export_preset;
}

ExportPreset* MacOSExportPresetWidget::getCurrentPreset() const
{
  return m_export_preset;
}

/* --------------------------- MacOSExportPresetWidget ---------------------- */

UnknownExportPresetWidget::UnknownExportPresetWidget(QWidget* parent) :
  ExportPresetWidget(parent),
  m_export_preset(nullptr)
{

}

UnknownExportPresetWidget::~UnknownExportPresetWidget() = default;

void UnknownExportPresetWidget::retranslateUi()
{
  // TODO Implementation
}

void UnknownExportPresetWidget::setCurrentPreset(ExportPreset* export_preset)
{
  m_export_preset = export_preset;
}

ExportPreset* UnknownExportPresetWidget::getCurrentPreset() const
{
  return m_export_preset;
}