#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/project.h>
#include <egnim/editor/document/document.h>
/* -------------------------------------------------------------------------- */

namespace Ui { class MainWindow; }

class PreferencesManager;
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
  [[nodiscard]] LanguageManager& getLanguageManager() const;
  [[nodiscard]] StyleManager& getStyleManager() const;
  [[nodiscard]] ActionManager& getActionManager() const;
  [[nodiscard]] PreferencesManager& getPreferencesManager() const;

  [[nodiscard]] Project* getCurrentProject() const;

protected:
  void closeEvent(QCloseEvent *event) override;
  void changeEvent(QEvent *event) override;

private Q_SLOTS:
  void projectChanged(Project* project);
  void documentChanged(Document* document);

  bool confirmSave(Project* project);
  bool confirmAllSave();

  void updateActions();
  void updateWindowTitle();
  void updateViewsAndToolbarsMenu();
  void updateRecentProjectFiles();

  void newProject(Project::Type type);
  void openProject();
  void clearRecent();
  void closeProject(int index);
  void openSettings();
  bool saveProject(Project* project);
  bool saveAllProjects();

  void newDocument(Document::Type type);
  void closeDocument();

  void performCut();
  void performCopy();
  void performPaste();
  void performDelete();

  void openAbout();
  
  bool openProject(const QString& file_name);

private:
  void writeSettings();
  void readSettings();

  void registerMenus();
  void registerActions();

  void retranslateUi();

private:
  QScopedPointer<Ui::MainWindow> m_ui;
  QScopedPointer<Preferences> m_preferences;

  Project* m_current_project;
  Document* m_current_document;
};

#endif //MAIN_WINDOW_H
