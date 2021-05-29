#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
/* -------------------------------------------------------------------------- */

namespace Ui { class MainWindow; }

class PreferencesManager;
class DocumentManager;
class LanguageManager;
class ActionManager;
class StyleManager;
class Document;

class MainWindow final : public QMainWindow
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

  [[nodiscard]] DocumentManager& getDocumentManager() const;
  [[nodiscard]] LanguageManager& getLanguageManager() const;
  [[nodiscard]] StyleManager& getStyleManager() const;
  [[nodiscard]] ActionManager& getActionManager() const;
  [[nodiscard]] PreferencesManager& getPreferencesManager() const;

  [[nodiscard]] Document* getCurrentDocument() const;

protected:
  void closeEvent(QCloseEvent *event) override;
  void changeEvent(QEvent *event) override;

private Q_SLOTS:
  void closeDocument(int index);
  void documentChanged(Document* document);

  void newProject();
  void openProject();

  bool saveDocument();
  bool saveDocumentAs();

private:
  bool confirmSave(Document* document);
  bool confirmAllSave();

  void writeSettings();
  void readSettings();

  void registerMenus();
  void registerActions();

  void retranslateUi();

private:
  QScopedPointer<Ui::MainWindow> m_ui;
  QScopedPointer<Preferences> m_preferences;
  Document* m_current_document;
};

#endif //MAIN_WINDOW_H
