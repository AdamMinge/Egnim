#ifndef NODES_VIEW_H
#define NODES_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsView>
/* -------------------------------------------------------------------------- */

class NodesScene;

class NodesView : public QGraphicsView
{
  Q_OBJECT

public:
  explicit NodesView(QWidget* parent = nullptr);
  ~NodesView() override;

  void setScene(NodesScene* scene);
  [[nodiscard]] NodesScene* getScene() const;
};

#endif //NODES_VIEW_H
