#ifndef NO_DOCUMENT_WIDGET_H
#define NO_DOCUMENT_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

namespace Ui { class NoDocumentWidget; }

class NoDocumentWidget : public QWidget
{
Q_OBJECT

public:
  explicit NoDocumentWidget(QWidget* parent = nullptr);
  ~NoDocumentWidget() override;

private:
  QScopedPointer<Ui::NoDocumentWidget> m_ui;
};

#endif //NO_DOCUMENT_WIDGET_H
