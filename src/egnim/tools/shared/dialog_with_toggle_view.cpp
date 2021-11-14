/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
#include <QActionEvent>
/* -------------------------------- Tools Shared ---------------------------- */
#include "egnim/tools/shared/dialog_with_toggle_view.h"
/* -------------------------------------------------------------------------- */

namespace tools {

QDialogWithToggleView::QDialogWithToggleView(QWidget* parent) :
  QDialog(parent),
  m_toggle_view(new QAction(this))
{
  m_toggle_view->setCheckable(true);

  connect(m_toggle_view, &QAction::toggled, this, &QDialogWithToggleView::setVisible);
  connect(this, &QDialogWithToggleView::windowTitleChanged, this, &QDialogWithToggleView::titleChanged);
}
QDialogWithToggleView::~QDialogWithToggleView() = default;

QAction* QDialogWithToggleView::toggleViewAction() const
{
  return m_toggle_view;
}

void QDialogWithToggleView::closeEvent(QCloseEvent* event)
{
  QDialog::closeEvent(event);

  if (event->isAccepted())
    m_toggle_view->setChecked(false);
}

void QDialogWithToggleView::titleChanged(const QString& title)
{
  m_toggle_view->setText(title);
}

} // namespace tools