#ifndef DIALOG_WITH_TOGGLE_VIEW_H
#define DIALOG_WITH_TOGGLE_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include "QDialog"
/* -------------------------------------------------------------------------- */

class QDialogWithToggleView : public QDialog
{
  Q_OBJECT

public:
  explicit QDialogWithToggleView(QWidget* parent = nullptr);
  ~QDialogWithToggleView() override;

  [[nodiscard]] QAction* toggleViewAction() const;

protected:
  void closeEvent(QCloseEvent* event) override;

private Q_SLOTS:
  void titleChanged(const QString& title);

private:
  QAction* m_toggle_view;
};

#endif //DIALOG_WITH_TOGGLE_VIEW_H
