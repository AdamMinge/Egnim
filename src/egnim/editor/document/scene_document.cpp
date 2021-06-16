/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document/scene_document.h>
/* -------------------------------------------------------------------------- */

std::unique_ptr<SceneDocument> SceneDocument::create(const QString& file_name)
{
  auto document = std::unique_ptr<SceneDocument>(new SceneDocument(file_name));
  document->save(file_name);

  return document;
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
