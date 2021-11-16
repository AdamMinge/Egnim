#ifndef INSPECTOR_DOCK_H
#define INSPECTOR_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class InspectorDock final : public QDockWidget
{
Q_OBJECT

public:
  explicit InspectorDock(QWidget* parent = nullptr);
  ~InspectorDock() override;

protected:
  void changeEvent(QEvent* event) override;

private:
  void retranslateUi();
};

#endif //INSPECTOR_DOCK_H
