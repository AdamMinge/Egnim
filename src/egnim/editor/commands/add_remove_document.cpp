/* ------------------------------------ Qt ---------------------------------- */
#include <QMessageBox>
#include <QFileInfo>
#include <QFile>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/commands/add_remove_document.h>
#include <egnim/editor/document/document.h>
#include <egnim/editor/project/project.h>
/* -------------------------------------------------------------------------- */

/* ----------------------------- AddRemoveDocument -------------------------- */

AddRemoveDocument::AddRemoveDocument(Command::Type type, Project& project, std::unique_ptr<Document> document) :
  Command(type),
  m_project(project),
  m_document(std::move(document))
{

}

AddRemoveDocument::~AddRemoveDocument() = default;

void AddRemoveDocument::addDocument()
{
  if(!m_document->save(m_document->getFileName()))
  {
    QMessageBox::critical(nullptr,
                          QObject::tr("Error Saving File"),
                          QObject::tr("Error saving document '%1'").arg(m_document->getFileName()));
  }

  m_project.addDocument(std::move(m_document));
}

void AddRemoveDocument::removeDocument()
{
  auto& project_to_remove = *m_project.getDocuments().back();
  if(QFileInfo::exists(project_to_remove.getFileName()))
  {
    auto reply = QMessageBox::question(nullptr,
                                       QObject::tr("Delete Document"),
                                       QObject::tr("Are you sure you want to delete document '%1'").arg(project_to_remove.getFileName()),
                                       QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes)
      QFile::remove(project_to_remove.getFileName());
  }

  m_document = m_project.removeDocument(project_to_remove);
}

/* -------------------------------- AddDocument ----------------------------- */

AddDocument::AddDocument(Project& project, std::unique_ptr<Document> document) :
  AddRemoveDocument(Type::AddDocument, project, std::move(document))
{

}

AddDocument::~AddDocument() = default;

void AddDocument::undo()
{
  removeDocument();
}

void AddDocument::redo()
{
  addDocument();
}

/* ------------------------------- RemoveDocument --------------------------- */

RemoveDocument::RemoveDocument(Project& project, std::unique_ptr<Document> document) :
  AddRemoveDocument(Type::RemoveDocument, project, std::move(document))
{

}

RemoveDocument::~RemoveDocument() = default;

void RemoveDocument::undo()
{
  addDocument();
}

void RemoveDocument::redo()
{
  removeDocument();
}

