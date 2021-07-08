#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
#include <QStackedWidget>
/* ----------------------------------- Local -------------------------------- */
#include "project/project.h"
#include "document/document.h"
/* -------------------------------------------------------------------------- */

namespace Ui { class MainWindow; }
class NoProjectWidget;
class ProjectDock;
class ConsoleDock;

class PreferencesManager;
class DocumentManager;
class LanguageManager;
class ProjectManager;
class ActionManager;
class StyleManager;

class MainWindow final : public QMainWindow
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

  [[nodiscard]] ProjectManager& getProjectManager() const;
  [[nodiscard]] DocumentManager& getDocumentManager() const;
  [[nodiscard]] LanguageManager& getLanguageManager() const;
  [[nodiscard]] StyleManager& getStyleManager() const;
  [[nodiscard]] ActionManager& getActionManager() const;
  [[nodiscard]] PreferencesManager& getPreferencesManager() const;

protected:
  void closeEvent(QCloseEvent *event) override;
  void changeEvent(QEvent *event) override;

private Q_SLOTS:
  void documentChanged(Document* document);
  void projectChanged(Project* project);

  bool confirmSave(Document* document);
  bool confirmAllSave();

  void updateActions();
  void updateWindowTitle();
  void updateViewsAndToolbarsMenu();
  void updateRecentProjectFiles();

  void newProject(Project::Type type);
  void openProject();
  void clearRecent();
  void closeProject();
  void openSettings();
  void exportProject();

  void newDocument(Document::Type type);
  void closeDocument(int index);
  bool saveDocument(Document* document);
  bool saveDocumentAs(Document* document);
  bool saveAllDocuments();

  void performCut();
  void performCopy();
  void performPaste();
  void performDelete();

  void openAbout();

private:
  void writeSettings();
  void readSettings();

  void registerMenus();
  void registerActions();
  void registerConnections();

  void retranslateUi();

private:
  QScopedPointer<Ui::MainWindow> m_ui;
  QScopedPointer<Preferences> m_preferences;

  QStackedWidget* m_stacked_widget;
  NoProjectWidget* m_no_project_widget;
  QMainWindow* m_project_window;

  ProjectDock* m_project_dock;
  ConsoleDock* m_console_dock;
};

#endif //MAIN_WINDOW_H
