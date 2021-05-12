/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
#include <QActionEvent>
/* ----------------------------------- Local -------------------------------- */
#include <widgets/dialog_with_toggle_view.h>
/* -------------------------------------------------------------------------- */

DialogWithToggleView::DialogWithToggleView(QWidget* parent) :
  QDialog(parent),
  m_toggle_view(new QAction(this))
{
  m_toggle_view->setCheckable(true);

  connect(m_toggle_view, &QAction::toggled, this, &DialogWithToggleView::setVisible);
  connect(this, &DialogWithToggleView::windowTitleChanged, this, &DialogWithToggleView::titleChanged);
}
DialogWithToggleView::~DialogWithToggleView() = default;

QAction* DialogWithToggleView::getToggleViewAction() const
{
  return m_toggle_view;
}

void DialogWithToggleView::closeEvent(QCloseEvent* event)
{
  QDialog::closeEvent(event);

  if (event->isAccepted())
    m_toggle_view->setChecked(false);
}

void DialogWithToggleView::titleChanged(const QString& title)
{
  m_toggle_view->setText(title);
}