#ifndef NO_EDITOR_WIDGET_H
#define NO_EDITOR_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

namespace Ui { class NoEditorWidget; }

class NoEditorWidget : public QWidget
{
  Q_OBJECT

public:
  explicit NoEditorWidget(QWidget* parent = nullptr);
  ~NoEditorWidget() override;

private:
  QScopedPointer<Ui::NoEditorWidget> m_ui;
};

#endif //NO_EDITOR_WIDGET_H
