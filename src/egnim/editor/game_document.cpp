/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/game_document.h>
/* -------------------------------------------------------------------------- */

GameDocument::GameDocument(QString file_name, QObject* parent) :
  Document(Type::Game, std::move(file_name), parent)
{

}

GameDocument::~GameDocument() = default;

const QDateTime& GameDocument::getLastModified() const
{
  return m_last_modified;
}

bool GameDocument::save(const QString& file_name)
{
  // TODO : save implementation //

  getUndoStack()->setClean();
  setFileName(file_name);
  m_last_modified = QFileInfo(file_name).lastModified();

  Q_EMIT saved();
  return true;
}
