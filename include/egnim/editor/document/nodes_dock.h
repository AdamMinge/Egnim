#ifndef NODES_DOCK_H
#define NODES_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class NodesDock final : public QDockWidget
{
Q_OBJECT

public:
  explicit NodesDock(QWidget* parent = nullptr);
  ~NodesDock() override;

protected:
  void changeEvent(QEvent* event) override;

private:
  void retranslateUi();
};

#endif //NODES_DOCK_H
