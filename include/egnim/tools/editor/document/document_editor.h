#ifndef DOCUMENT_EDITOR_H
#define DOCUMENT_EDITOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class Document;
class QDialogWithToggleView;

class DocumentEditor : public QObject
{
  Q_OBJECT

public:
  enum StandardAction {
    CutAction            = 0x01,
    CopyAction           = 0x02,
    PasteAction          = 0x04,
    DeleteAction         = 0x08
  };
  Q_DECLARE_FLAGS(StandardActions, StandardAction)
  Q_FLAG(StandardActions)

public:
  ~DocumentEditor() override;

  virtual void setCurrentDocument(Document* document) = 0;

  virtual void addDocument(Document* document) = 0;
  virtual void removeDocument(Document* document) = 0;

  [[nodiscard]] virtual Document* getCurrentDocument() const = 0;
  [[nodiscard]] virtual QWidget* getEditorWidget() const = 0;

  virtual void saveState() = 0;
  virtual void restoreState() = 0;

  [[nodiscard]] virtual QList<QDockWidget*> getDockWidgets() const = 0;
  [[nodiscard]] virtual QList<QDialogWithToggleView*> getDialogWidgets() const = 0;

  virtual void performStandardAction(StandardAction standard_action) = 0;
  [[nodiscard]] virtual StandardActions getEnabledStandardActions() const = 0;

Q_SIGNALS:
  void enabledStandardActionsChanged();

protected:
  explicit DocumentEditor(QObject* parent = nullptr);
};

#endif //DOCUMENT_EDITOR_H
