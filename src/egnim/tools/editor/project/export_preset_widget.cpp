/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/project/export_preset_widget.h"
#include "egnim/tools/editor/project/export_preset.h"
/* -------------------------------- Tools Shared ---------------------------- */
#include <egnim/tools/shared/qtdialog/qtextendedfiledialog.h>
#include <egnim/tools/shared/qtpropertybrowser/qtpropertymanager.h>
#include <egnim/tools/shared/qtpropertybrowser/qtvariantproperty.h>
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
  m_ui(new Ui::ExportPresetWidget()),
  m_variant_property_manager(new tools::QtVariantPropertyManager(this)),
  m_group_property_manager(new tools::QtGroupPropertyManager(this)),
  m_build_type_names({"Debug", "Release"}),
  m_build_version_names({"x32", "x64"})
{
  m_ui->setupUi(this);

  connect(m_ui->m_name_edit, &QLineEdit::textChanged, this, [this](auto&& name){
    if(getCurrentPreset()) getCurrentPreset()->setName(std::forward<decltype(name)>(name));});

  connect(m_ui->m_export_path_edit, &QLineEdit::textChanged, this, [this](auto&& path){
    if(getCurrentPreset()) getCurrentPreset()->setExportPath(std::forward<decltype(path)>(path));});

  connect(m_ui->m_browse_button, &QPushButton::pressed, this, &BaseExportPresetWidget::onBrowsePressed);

  addProperties();

  connect(m_variant_property_manager, &tools::QtVariantPropertyManager::valueChanged,
          this, &BaseExportPresetWidget::onPropertyChanged);

  m_ui->m_property_browser->setFactoryForManager(
      m_variant_property_manager, new tools::QtVariantEditorFactory(this));

  retranslateUi();
}

BaseExportPresetWidget::~BaseExportPresetWidget() = default;

void BaseExportPresetWidget::setCurrentPreset(ExportPreset* export_preset)
{
  m_ui->m_name_edit->setText(export_preset ? export_preset->getName() : QString{});
  m_ui->m_export_path_edit->setText(export_preset ? export_preset->getExportPath() : QString{});

  m_id_to_property[PropertyId::BuildType]->setValue(
      export_preset ? static_cast<int>(export_preset->getBuildType()) : QVariant{});
  m_id_to_property[PropertyId::BuildVersion]->setValue(
      export_preset ? static_cast<int>(export_preset->getBuildVersion()) : QVariant{});
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

tools::QtVariantProperty* BaseExportPresetWidget::addProperty(
    PropertyId property_id, int type, const QString& name, tools::QtProperty* parent)
{
  auto property = m_variant_property_manager->addProperty(type, name);
  if(!property)
    property = m_variant_property_manager->addProperty(QMetaType::QString, name);

  if(type == QMetaType::Bool)
    property->setAttribute(QLatin1String("textVisible"), false);

  m_property_to_id.insert(std::make_pair(property, property_id));
  m_id_to_property.insert(std::make_pair(property_id, property));

  if(parent)
    parent->addSubProperty(property);

  return property;
}

tools::QtVariantProperty* BaseExportPresetWidget::addEnumProperty(
    PropertyId property_id, const QStringList& values, const QString& name, tools::QtProperty* parent)
{
  auto property = addProperty(property_id, tools::QtVariantPropertyManager::enumTypeId(), name, parent);
  property->setAttribute("enumNames", values);
  return property;
}

tools::QtProperty* BaseExportPresetWidget::addGroupProperty(const QString& name, tools::QtProperty* parent)
{
  auto property = m_group_property_manager->addProperty(name);

  if(parent)
    parent->addSubProperty(property);

  return property;
}

void BaseExportPresetWidget::addPlatformProperties() {}

void BaseExportPresetWidget::onPlatformPropertyChanged(tools::QtProperty *property, const QVariant &val) {}

void BaseExportPresetWidget::onBrowsePressed()
{
  const auto file_dialog_options =
      QFileDialog::Options() |
      QFileDialog::Option::DontUseNativeDialog;

  auto filter = QString("Project Executable (*%1)").arg(getCurrentPreset()->getExecutableExtension());
  auto dir_path = tools::QtExtendedFileDialog::getSaveFileName(
      this, tr("Export Project"), m_ui->m_export_path_edit->text(),
      filter, &filter, file_dialog_options);

  if(dir_path.isEmpty())
    return;

  m_ui->m_export_path_edit->setText(dir_path);
}

void BaseExportPresetWidget::onPropertyChanged(tools::QtProperty *property, const QVariant &val)
{
  if(!getCurrentPreset())
    return;

  if(!m_property_to_id.contains(property))
    return;

  auto preset = getCurrentPreset();
  const auto property_id = m_property_to_id[property];
  switch(property_id)
  {
    case PropertyId::BuildType:
      preset->setBuildType(static_cast<ExportPreset::BuildType>(val.toInt()));
      break;

    case PropertyId::BuildVersion:
      preset->setBuildVersion(static_cast<ExportPreset::BuildVersion>(val.toInt()));
      break;

    default:
      onPlatformPropertyChanged(property, val);
      break;
  }
}

void BaseExportPresetWidget::retranslateUi()
{
  m_ui->retranslateUi(this);
}

void BaseExportPresetWidget::addProperties()
{
  auto build_properties_group = addGroupProperty(tr("Build"));
  addEnumProperty(PropertyId::BuildType, m_build_type_names,
              tr("type"), build_properties_group);
  addEnumProperty(PropertyId::BuildVersion, m_build_version_names,
              tr("version"), build_properties_group);

  m_ui->m_property_browser->addProperty(build_properties_group);

  addPlatformProperties();
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

void WindowsExportPresetWidget::addPlatformProperties()
{

}

void WindowsExportPresetWidget::onPlatformPropertyChanged(tools::QtProperty *property, const QVariant &val)
{

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