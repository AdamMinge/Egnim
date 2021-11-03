/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "project/export_preset_widget.h"
#include "project/export_preset.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_export_preset_widget.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- ExportPresetWidget ------------------------- */

ExportPresetWidget::ExportPresetWidget(QWidget* parent) :
  QWidget(parent)
{

}

ExportPresetWidget::~ExportPresetWidget() = default;

/* --------------------------- BaseExportPresetWidget ----------------------- */

BaseExportPresetWidget::BaseExportPresetWidget(QWidget* parent) :
  ExportPresetWidget(parent),
  m_ui(new Ui::ExportPresetWidget())
{
  m_ui->setupUi(this);

  connect(m_ui->m_name_edit, &QLineEdit::textChanged, this, [this](auto&& name){
    if(getCurrentPreset()) getCurrentPreset()->setName(std::forward<decltype(name)>(name));});

  connect(m_ui->m_export_path_edit, &QLineEdit::textChanged, this, [this](auto&& path){
    if(getCurrentPreset()) getCurrentPreset()->setExportPath(std::forward<decltype(path)>(path));});
}

BaseExportPresetWidget::~BaseExportPresetWidget() = default;

void BaseExportPresetWidget::setCurrentPreset(ExportPreset* export_preset)
{
  m_ui->m_name_edit->setText(getCurrentPreset() ? getCurrentPreset()->getName() : QString{});
  m_ui->m_export_path_edit->setText(getCurrentPreset() ? getCurrentPreset()->getExportPath() : QString{});
}

void BaseExportPresetWidget::changeEvent(QEvent* event)
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

void BaseExportPresetWidget::retranslateUi()
{
  m_ui->retranslateUi(this);
}

/* ------------------------- WindowsExportPresetWidget ---------------------- */

WindowsExportPresetWidget::WindowsExportPresetWidget(QWidget* parent) :
  BaseExportPresetWidget(parent),
  m_export_preset(nullptr)
{

}

WindowsExportPresetWidget::~WindowsExportPresetWidget() = default;

void WindowsExportPresetWidget::setCurrentPreset(ExportPreset* export_preset)
{
  auto current_export_preset = dynamic_cast<WindowsExportPreset*>(export_preset);
  Q_ASSERT(current_export_preset || !export_preset);

  m_export_preset = current_export_preset;
  BaseExportPresetWidget::setCurrentPreset(m_export_preset);
}

ExportPreset* WindowsExportPresetWidget::getCurrentPreset() const
{
  return m_export_preset;
}

/* -------------------------- LinuxExportPresetWidget ----------------------- */

LinuxExportPresetWidget::LinuxExportPresetWidget(QWidget* parent) :
  BaseExportPresetWidget(parent),
  m_export_preset(nullptr)
{

}

LinuxExportPresetWidget::~LinuxExportPresetWidget() = default;

void LinuxExportPresetWidget::setCurrentPreset(ExportPreset* export_preset)
{
  auto current_export_preset = dynamic_cast<LinuxExportPreset*>(export_preset);
  Q_ASSERT(current_export_preset || !export_preset);

  m_export_preset = current_export_preset;
  BaseExportPresetWidget::setCurrentPreset(m_export_preset);
}

ExportPreset* LinuxExportPresetWidget::getCurrentPreset() const
{
  return m_export_preset;
}

/* --------------------------- MacOSExportPresetWidget ---------------------- */

MacOSExportPresetWidget::MacOSExportPresetWidget(QWidget* parent) :
  BaseExportPresetWidget(parent),
  m_export_preset(nullptr)
{

}

MacOSExportPresetWidget::~MacOSExportPresetWidget() = default;

void MacOSExportPresetWidget::setCurrentPreset(ExportPreset* export_preset)
{
  auto current_export_preset = dynamic_cast<MacOSExportPreset*>(export_preset);
  Q_ASSERT(current_export_preset || !export_preset);

  m_export_preset = current_export_preset;
  BaseExportPresetWidget::setCurrentPreset(m_export_preset);
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

void UnknownExportPresetWidget::setCurrentPreset(ExportPreset* export_preset)
{
  m_export_preset = export_preset;
}

ExportPreset* UnknownExportPresetWidget::getCurrentPreset() const
{
  return m_export_preset;
}