/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "project/export_preset_widget.h"
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
  ExportPresetWidget(parent)
{

}

WindowsExportPresetWidget::~WindowsExportPresetWidget() = default;

void WindowsExportPresetWidget::retranslateUi()
{
  // TODO implementation
}

/* -------------------------- LinuxExportPresetWidget ----------------------- */

LinuxExportPresetWidget::LinuxExportPresetWidget(QWidget* parent) :
  ExportPresetWidget(parent)
{

}

LinuxExportPresetWidget::~LinuxExportPresetWidget() = default;

void LinuxExportPresetWidget::retranslateUi()
{
  // TODO implementation
}

/* --------------------------- MacOSExportPresetWidget ---------------------- */

MacOSExportPresetWidget::MacOSExportPresetWidget(QWidget* parent) :
  ExportPresetWidget(parent)
{

}

MacOSExportPresetWidget::~MacOSExportPresetWidget() = default;

void MacOSExportPresetWidget::retranslateUi()
{
  // TODO implementation
}