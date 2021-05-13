#ifndef NO_EDITOR_WIDGET_H
#define NO_EDITOR_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

class NoEditorWidget : public QWidget
{
  Q_OBJECT

public:
  explicit NoEditorWidget(QWidget* parent = nullptr);
  ~NoEditorWidget() override;
};

#endif //NO_EDITOR_WIDGET_H
