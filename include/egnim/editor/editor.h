#ifndef EDITOR_H
#define EDITOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class Document;
class DialogWithToggleView;

class Editor : public QObject
{
  Q_OBJECT

public:
  explicit Editor(QObject* parent = nullptr);
  ~Editor() override;

  virtual void setCurrentDocument(Document* document) = 0;

  [[nodiscard]] virtual Document* getCurrentDocument() const = 0;
  [[nodiscard]] virtual QWidget* getEditorWidget() const = 0;

  virtual void saveState() = 0;
  virtual void restoreState() = 0;

  [[nodiscard]] virtual QList<QDockWidget*> getDockWidgets() const = 0;
  [[nodiscard]] virtual QList<DialogWithToggleView*> getDialogWidgets() const = 0;
};

#endif //EDITOR_H
