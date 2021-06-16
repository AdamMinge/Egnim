/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
#include <QFile>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/project.h>
#include <egnim/editor/project/project_serializer.h>
#include <egnim/editor/document/document.h>
/* -------------------------------------------------------------------------- */

Project::Project(Type type, QObject* parent) :
  QObject(parent),
  m_type(type),
  m_undo_stack(new QUndoStack(this))
{
  connect(m_undo_stack, &QUndoStack::cleanChanged, this, &Project::modifiedChanged);
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

const QString& Project::getFileName() const
{
  return m_file_name;
}

QString Project::getDisplayName() const
{
  QString displayName = QFileInfo(m_file_name).fileName();
  if (displayName.isEmpty())
    displayName = tr("untitled.egn-pro");

  return displayName;
}

void Project::setLastModified(const QDateTime& date)
{
  m_last_modified = date;
}

const QDateTime& Project::getLastModified() const
{
  return m_last_modified;
}

bool Project::isModified() const
{
  return !m_undo_stack->isClean();
}

QUndoStack* Project::getUndoStack() const
{
  return m_undo_stack;
}

void Project::addDocument(std::unique_ptr<Document> document)
{
  m_documents.push_back(std::move(document));
  Q_EMIT addedDocument(m_documents.front().get());
}

void Project::removeDocument(const Document& document)
{
  auto found_document = std::find_if(m_documents.begin(), m_documents.end(),
                                     [document = std::addressof(document)](auto& current_document){
    return current_document.get() == document;
  });

  if(found_document == m_documents.end())
    return;

  Q_EMIT removedDocument((*found_document).get());
  m_documents.erase(found_document);
}

void Project::removeAllDocuments()
{
  while(!m_documents.empty())
    removeDocument(*m_documents.front());
}

const std::list<std::unique_ptr<Document>>& Project::getDocuments() const
{
  return m_documents;
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

  getUndoStack()->setClean();
  setLastModified(QFileInfo(getFileName()).lastModified());
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
  {
    project->setFileName(file_name);
    project->setLastModified(QFileInfo(file_name).lastModified());
  }

  return project;
}

QString Project::getProjectFileFilter()
{
  auto filter = QString{};

  filter.append(tr("Game Project (*%1)").arg(getProjectExtension(Type::Game)));

  return filter;
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
      return ".egn-pro";
  }

  return QString{};
}
