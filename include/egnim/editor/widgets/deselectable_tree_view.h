#ifndef DESELECTABLE_TREE_VIEW_H
#define DESELECTABLE_TREE_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTreeView>
/* -------------------------------------------------------------------------- */

class DeselectableTreeView : public QTreeView
{
public:
  explicit DeselectableTreeView(QWidget *parent = nullptr);
  ~DeselectableTreeView() override;

private:
  void mousePressEvent(QMouseEvent *event) override;
};

#endif //DESELECTABLE_TREE_VIEW_H
