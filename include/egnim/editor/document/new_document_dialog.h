#ifndef NEW_DOCUMENT_DIALOG_H
#define NEW_DOCUMENT_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* ----------------------------------- Local -------------------------------- */
#include "document/document.h"
/* -------------------------------------------------------------------------- */

namespace Ui { class NewSceneDocumentDialog; }

class NewDocumentDialog : public QDialog
{
  Q_OBJECT

public:
  ~NewDocumentDialog() override;

  [[nodiscard]] virtual std::unique_ptr<Document> create() = 0;

public:
  static std::unique_ptr<Document> createDocument(Document::Type type);

protected:
  explicit NewDocumentDialog(QWidget* parent = nullptr);
};

class NewSceneDocumentDialog : public NewDocumentDialog
{
  Q_OBJECT

public:
  explicit NewSceneDocumentDialog(QWidget* parent = nullptr);
  ~NewSceneDocumentDialog() override;

  [[nodiscard]] std::unique_ptr<Document> create() override;

protected:
  void changeEvent(QEvent* event) override;

private Q_SLOTS:
  void onBrowsePressed();
  void validate();

private:
  void retranslateUi();

private:
  QScopedPointer<Ui::NewSceneDocumentDialog> m_ui;
};

#endif //NEW_DOCUMENT_DIALOG_H
