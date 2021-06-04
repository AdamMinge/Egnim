/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/project.h>
#include <egnim/editor/document/document.h>
/* -------------------------------------------------------------------------- */

Project::Project(Type type, QString file_name, QObject* parent) :
  QObject(parent),
  m_type(type),
  m_file_name(std::move(file_name))
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

const QString& Project::getFileName() const
{
  return m_file_name;
}

QString Project::getDisplayName() const
{
  QString displayName = QFileInfo(m_file_name).fileName();
  if (displayName.isEmpty())
    displayName = tr("untitled.egn");

  return displayName;
}

bool Project::isModified() const
{
  return std::any_of(m_documents.begin(), m_documents.end(), [](auto& document){
    return document->isModified();
  });
}

void Project::addDocument(std::unique_ptr<Document> document)
{
  m_documents.push_back(std::move(document));

  connect(m_documents.front().get(), &Document::modifiedChanged, this, &Project::modifiedChanged);

  Q_EMIT removedDocument(m_documents.front().get());
}

void Project::removeDocument(const Document& document)
{
  auto found_document = std::find_if(m_documents.begin(), m_documents.end(),
                                     [document = std::addressof(document)](auto& current_document){
    return current_document.get() == document;
  });

  if(found_document == m_documents.end())
    return;

  m_documents.front().get()->disconnect(this);

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
