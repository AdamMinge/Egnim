#ifndef DOCUMENT_EDITOR_H
#define DOCUMENT_EDITOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class Document;
class DialogWithToggleView;

class DocumentEditor : public QObject
{
  Q_OBJECT

public:
  ~DocumentEditor() override;

  virtual void setCurrentDocument(Document* document) = 0;

  [[nodiscard]] virtual Document* getCurrentDocument() const = 0;
  [[nodiscard]] virtual QWidget* getEditorWidget() const = 0;

  virtual void saveState() = 0;
  virtual void restoreState() = 0;

  [[nodiscard]] virtual QList<QDockWidget*> getDockWidgets() const = 0;
  [[nodiscard]] virtual QList<DialogWithToggleView*> getDialogWidgets() const = 0;

protected:
  explicit DocumentEditor(QObject* parent = nullptr);
};

#endif //DOCUMENT_EDITOR_H
