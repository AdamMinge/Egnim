/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/document/nodes_view.h"
#include "egnim/tools/editor/document/nodes_scene.h"
/* -------------------------------------------------------------------------- */

NodesView::NodesView(QWidget* parent) :
  QGraphicsView(parent)
{

}

NodesView::~NodesView() = default;

void NodesView::setScene(NodesScene* scene)
{
  QGraphicsView::setScene(scene);
}

NodesScene* NodesView::getScene() const
{
  auto nodes_scene = dynamic_cast<NodesScene*>(scene());
  Q_ASSERT(nodes_scene || !scene());

  return nodes_scene;
}
