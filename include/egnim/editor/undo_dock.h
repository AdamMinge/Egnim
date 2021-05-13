#ifndef UNDO_DOCK_H
#define UNDO_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QUndoStack>
#include <QUndoView>
/* -------------------------------------------------------------------------- */

class UndoDock final : public QDockWidget
{
  Q_OBJECT

public:
  explicit UndoDock(QWidget* parent = nullptr);
  ~UndoDock() override = default;

  UndoDock(UndoDock&&) = delete;
  UndoDock(const UndoDock&) = delete;

  UndoDock& operator=(UndoDock&&) = delete;
  UndoDock& operator=(const UndoDock&) = delete;

  void setStack(QUndoStack* stack);

protected:
  void changeEvent(QEvent* event) override;

private:
  void retranslateUi();

private:
  QUndoView* m_undo_view;
};

#endif //UNDO_DOCK_H
