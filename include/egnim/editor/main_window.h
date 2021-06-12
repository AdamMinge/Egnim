#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
/* -------------------------------------------------------------------------- */

namespace Ui { class MainWindow; }

class PreferencesManager;
class LanguageManager;
class ProjectManager;
class ActionManager;
class StyleManager;
class Project;

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
  void closeProject(int index);
  void projectChanged(Project* project);

  bool confirmSave(Project* project);
  bool confirmAllSave();

  bool saveProject(Project* project);
  bool saveAllProjects();

  void newProject();
  void openProject();
  void clearRecent();
  void openSettings();
  void openAbout();

  void updateActions();
  void updateWindowTitle();
  void updateViewsAndToolbarsMenu();

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
};

#endif //MAIN_WINDOW_H
