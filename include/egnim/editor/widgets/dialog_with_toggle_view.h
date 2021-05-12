#ifndef DIALOG_WITH_TOGGLE_VIEW_H
#define DIALOG_WITH_TOGGLE_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* -------------------------------------------------------------------------- */

class DialogWithToggleView : public QDialog
{
  Q_OBJECT

public:
  explicit DialogWithToggleView(QWidget* parent = nullptr);
  ~DialogWithToggleView() override;

  [[nodiscard]] QAction* getToggleViewAction() const;

protected:
  void closeEvent(QCloseEvent* event) override;

private Q_SLOTS:
  void titleChanged(const QString& title);

private:
  QAction* m_toggle_view;
};

#endif //DIALOG_WITH_TOGGLE_VIEW_H
