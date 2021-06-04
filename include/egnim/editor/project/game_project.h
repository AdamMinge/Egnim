#ifndef GAME_PROJECT_H
#define GAME_PROJECT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDateTime>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/project.h>
/* -------------------------------------------------------------------------- */

class GameProject : public Project
{
  Q_OBJECT

public:
  static std::unique_ptr<GameProject> create(QString file_name);
  static std::unique_ptr<GameProject> load(QString file_name);

public:
  ~GameProject() override;

  [[nodiscard]] const QDateTime& getLastModified() const;

  bool save() override;

Q_SIGNALS:
  void saved();

protected:
  explicit GameProject(QString file_name, QObject* parent = nullptr);

private:
  QDateTime m_last_modified;
};

#endif //GAME_PROJECT_H
