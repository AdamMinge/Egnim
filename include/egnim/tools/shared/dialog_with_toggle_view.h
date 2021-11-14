#ifndef EGNIM_TOOLS_DIALOG_WITH_TOGGLE_VIEW_H
#define EGNIM_TOOLS_DIALOG_WITH_TOGGLE_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include "QDialog"
/* -------------------------------- Tools Shared ---------------------------- */
#include <egnim/tools/shared/export.h>
/* -------------------------------------------------------------------------- */


namespace tools
{

  class TOOLS_SHARED_API QDialogWithToggleView : public QDialog
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

} // namespace tools


#endif //EGNIM_TOOLS_DIALOG_WITH_TOGGLE_VIEW_H
