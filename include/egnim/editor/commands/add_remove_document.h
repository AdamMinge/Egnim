#ifndef ADD_REMOVE_DOCUMENT_H
#define ADD_REMOVE_DOCUMENT_H

/* ----------------------------------- Local -------------------------------- */
#include "commands/command.h"
/* -------------------------------------------------------------------------- */

class Document;
class Project;

class AddRemoveDocument : public Command
{
public:
  ~AddRemoveDocument() override;

protected:
  explicit AddRemoveDocument(Command::Type type, Project& project, std::unique_ptr<Document> document);

  void addDocument();
  void removeDocument();

private:
  Project& m_project;
  std::unique_ptr<Document> m_document;
};

class AddDocument : public AddRemoveDocument
{
public:
  explicit AddDocument(Project& project, std::unique_ptr<Document> document);
  ~AddDocument() override;

  void undo() override;
  void redo() override;
};

class RemoveDocument : public AddRemoveDocument
{
public:
  explicit RemoveDocument(Project& project, std::unique_ptr<Document> document);
  ~RemoveDocument() override;

  void undo() override;
  void redo() override;
};

#endif //ADD_REMOVE_DOCUMENT_H
