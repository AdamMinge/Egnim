#ifndef ACTION_MANAGER_H
#define ACTION_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QHash>
#include <QMenu>
#include <QAction>
#include <QObject>
#include <QScopedPointer>
/* -------------------------------------------------------------------------- */

class ActionManager : public QObject
{
  Q_OBJECT

public:
  static ActionManager& getInstance();
  static void deleteInstance();

public:
  ~ActionManager() override;

  void registerAction(QAction* action, const QString& id);
  void unregisterAction(QAction* action, const QString& id);

  void registerMenu(QMenu* menu, const QString& id);
  void unregisterMenu(const QString& id);

  [[nodiscard]] QAction* findAction(const QString& id) const;
  [[nodiscard]] QMenu* findMenu(const QString& id) const;

  [[nodiscard]] QList<QString> getActions() const;
  [[nodiscard]] QList<QString> getMenus() const;

  void setCustomShortcut(const QString& id, const QKeySequence& keySequence);
  [[nodiscard]] bool hasCustomShortcut(const QString& id) const;

  void resetCustomShortcut(const QString& id);
  void resetAllCustomShortcuts();

Q_SIGNALS:
  void actionChanged(const QString& id);

private:
  void applyShortcut(QAction *action, const QKeySequence &shortcut);
  void updateToolTipWithShortcut(QAction *action);

private:
  explicit ActionManager();

private:
  static QScopedPointer<ActionManager> m_instance;

  QMultiHash<QString, QAction*> m_actions;
  QHash<QString, QMenu*> m_menus;

  QHash<QString, QKeySequence> m_default_shortcuts;
  QHash<QString, QKeySequence> m_custom_shortcuts;
  QHash<QString, QKeySequence> m_last_known_shortcuts;

  bool m_applying_shortcut;
  bool m_applying_tooltip_with_shortcut;
  bool m_resetting_shortcut;
};

#endif //ACTION_MANAGER_H
