/* ------------------------------------ Qt ---------------------------------- */
#include <QVBoxLayout>
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/undo_dock.h>
/* -------------------------------------------------------------------------- */

UndoDock::UndoDock(QWidget* parent) :
  QDockWidget(parent),
  m_undo_view(new QUndoView(this))
{
  setObjectName(QLatin1String("History"));

  m_undo_view->setUniformItemSizes(true);

  auto widget = new QWidget(this);
  auto layout = new QVBoxLayout(widget);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(m_undo_view);
  widget->setLayout(layout);

  setWidget(widget);
  retranslateUi();
}

UndoDock::~UndoDock() = default;

void UndoDock::setStack(QUndoStack* stack)
{
  m_undo_view->setStack(stack);
}

void UndoDock::changeEvent(QEvent* event)
{
  QDockWidget::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void UndoDock::retranslateUi()
{
  setWindowTitle(tr("History"));
  m_undo_view->setEmptyLabel(tr("<empty>"));
}