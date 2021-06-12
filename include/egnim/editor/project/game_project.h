#ifndef GAME_PROJECT_H
#define GAME_PROJECT_H

/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/project.h>
/* -------------------------------------------------------------------------- */

class GameProject : public Project
{
  Q_OBJECT

public:
  static std::unique_ptr<GameProject> create(const QString& file_name);

public:
  ~GameProject() override;

protected:
  explicit GameProject(QString file_name, QObject* parent = nullptr);
};

#endif //GAME_PROJECT_H
