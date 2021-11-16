/* ------------------------------------ Qt ---------------------------------- */
#include <QImageReader>
#include <QFileInfo>
#include <QFile>
/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/project/project.h"
#include "egnim/tools/editor/project/project_serializer.h"
#include "egnim/tools/editor/project/export_preset_list_model.h"
#include "egnim/tools/editor/document/document.h"
/* -------------------------------------------------------------------------- */

Project::Project(Type type, QObject* parent) :
  QObject(parent),
  m_type(type),
  m_export_preset_model(new ExportPresetListModel(this))
{

}

Project::~Project() = default;

Project::Type Project::getType() const
{
  return m_type;
}

void Project::setFileName(const QString& file_name)
{
  if(m_file_name == file_name)
    return;

  auto old_file_name = m_file_name;
  m_file_name = file_name;

  Q_EMIT fileNameChanged(file_name, old_file_name);
}

QString Project::getFileName() const
{
  return m_file_name;
}

QDir Project::getDirectory() const
{
  return QFileInfo(m_file_name).absoluteDir();
}

QString Project::getDisplayName() const
{
  QString displayName = QFileInfo(m_file_name).fileName();
  if (displayName.isEmpty())
    displayName = tr("untitled.%1").arg(getProjectExtension());

  return displayName;
}

QDateTime Project::getLastModified() const
{
  return QFileInfo(m_file_name).lastModified();
}

bool Project::save(const QString& file_name)
{
  auto serializer = ProjectSerializer();
  auto bytearray = serializer.serialize(*this);

  auto file = QFile(file_name);
  if(!file.open(QIODevice::WriteOnly))
    return false;

  file.write(bytearray);
  file.close();

  setFileName(file_name);

  Q_EMIT saved();
  return true;
}

std::unique_ptr<Project> Project::load(const QString& file_name)
{
  auto file = QFile(file_name);
  if(!file.open(QIODevice::ReadOnly))
    return nullptr;

  auto array = file.readAll();
  auto serializer = ProjectSerializer();

  auto project = serializer.deserialize(array);
  if(project)
    project->setFileName(file_name);

  return project;
}

QString Project::getProjectFileFilter()
{
  auto filter = QString{};

  filter.append(tr("Game Project (*.%1)").arg(getProjectExtension(Type::Game)));

  return filter;
}

QStringList Project::projectSupportedFormats()
{
  auto supported_formats = QStringList();

  auto documents_extensions = Document::getDocumentExtensions();
  std::transform(documents_extensions.begin(), documents_extensions.end(), documents_extensions.begin(),
                 [](auto& extension){ return QString("*.%1").arg(extension); });

  auto image_extensions = QStringList();
  for(auto& extension : QImageReader::supportedImageFormats())
    image_extensions.append(QString("*.%1").arg(QString::fromLocal8Bit(extension)));

  supported_formats << documents_extensions
                    << image_extensions;

  return supported_formats;
}

QString Project::getProjectExtension() const
{
  return getProjectExtension(m_type);
}

QString Project::getProjectExtension(Type type)
{
  switch(type)
  {
    case Type::Game:
      return "egn-game";
  }

  return QString{};
}

ExportPresetListModel* Project::getExportPresetModel() const
{
  return m_export_preset_model;
}
