/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document/scene_document.h>
/* -------------------------------------------------------------------------- */

std::unique_ptr<SceneDocument> SceneDocument::create()
{
  auto document = std::unique_ptr<SceneDocument>(new SceneDocument());
  return document;
}

SceneDocument::SceneDocument(QObject* parent) :
  Document(Type::Scene, parent)
{

}

SceneDocument::~SceneDocument() = default;
