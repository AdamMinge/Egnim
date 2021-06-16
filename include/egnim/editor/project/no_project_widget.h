#ifndef NO_PROJECT_WIDGET_H
#define NO_PROJECT_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

namespace Ui { class NoProjectWidget; }

class NoProjectWidget : public QWidget
{
  Q_OBJECT

public:
  explicit NoProjectWidget(QWidget* parent = nullptr);
  ~NoProjectWidget() override;

private:
  QScopedPointer<Ui::NoProjectWidget> m_ui;
};

#endif //NO_PROJECT_WIDGET_H
