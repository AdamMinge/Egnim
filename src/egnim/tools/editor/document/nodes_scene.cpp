/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/document/nodes_scene.h"
/* -------------------------------------------------------------------------- */

NodesScene::NodesScene(QObject* parent) :
  QGraphicsScene(parent),
  m_scene_document(nullptr)
{

}

NodesScene::~NodesScene() = default;

void NodesScene::setSceneDocument(SceneDocument* scene_document)
{
  if(m_scene_document == scene_document)
    return;

  m_scene_document = scene_document;
}

SceneDocument* NodesScene::getSceneDocument() const
{
  return m_scene_document;
}
