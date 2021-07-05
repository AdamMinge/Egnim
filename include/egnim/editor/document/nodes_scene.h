#ifndef NODES_SCENE_H
#define NODES_SCENE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsScene>
/* -------------------------------------------------------------------------- */

class SceneDocument;

class NodesScene : public QGraphicsScene
{
Q_OBJECT

public:
  explicit NodesScene(QObject* parent = nullptr);
  ~NodesScene() override;

  void setSceneDocument(SceneDocument* scene_document);
  [[nodiscard]] SceneDocument* getSceneDocument() const;

private:
  SceneDocument* m_scene_document;
};


#endif //NODES_SCENE_H
