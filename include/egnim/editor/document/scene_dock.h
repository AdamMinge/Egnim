#ifndef SCENE_DOCK_H
#define SCENE_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class SceneDock final : public QDockWidget
{
Q_OBJECT

public:
  explicit SceneDock(QWidget* parent = nullptr);
  ~SceneDock() override;

protected:
  void changeEvent(QEvent* event) override;

private:
  void retranslateUi();
};

#endif //SCENE_DOCK_H
