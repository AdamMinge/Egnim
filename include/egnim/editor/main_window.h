#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
/* -------------------------------------------------------------------------- */

class DocumentManager;
class LanguageManager;
class StyleManager;

class Document;

class MainWindow final : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

  [[nodiscard]] DocumentManager& getDocumentManager() const;
  [[nodiscard]] LanguageManager& getLanguageManager() const;
  [[nodiscard]] StyleManager& getStyleManager() const;

  [[nodiscard]] Document* getCurrentDocument() const;

protected:
  void closeEvent(QCloseEvent *event) override;
  void changeEvent(QEvent *event) override;

private Q_SLOTS:
  void closeDocument(int index);
  void documentChanged(Document* document);

private:
  bool confirmSave(Document* document);
  bool confirmAllSave();

  void writeSettings();
  void readSettings();

  void retranslateUi();

private:
  DocumentManager& m_document_manager;
  LanguageManager& m_language_manager;
  StyleManager& m_style_manager;

  Document* m_current_document;
};

#endif //MAIN_WINDOW_H
