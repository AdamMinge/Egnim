/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document/scene_document.h>
/* -------------------------------------------------------------------------- */

std::unique_ptr<SceneDocument> SceneDocument::create(QString file_name)
{
  auto document = std::unique_ptr<SceneDocument>(new SceneDocument(std::move(file_name)));
  document->save();

  return document;
}

std::unique_ptr<SceneDocument> SceneDocument::load(QString file_name)
{
  // TODO : implementation //
  return nullptr;
}

SceneDocument::SceneDocument(QString file_name, QObject* parent) :
  Document(Type::Scene, std::move(file_name), parent)
{

}

SceneDocument::~SceneDocument() = default;

const QDateTime& SceneDocument::getLastModified() const
{
  return m_last_modified;
}

bool SceneDocument::save()
{
  // TODO : save implementation //

  getUndoStack()->setClean();
  m_last_modified = QFileInfo(getFileName()).lastModified();

  Q_EMIT saved();
  return true;
}
