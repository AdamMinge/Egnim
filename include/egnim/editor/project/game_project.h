#ifndef GAME_PROJECT_H
#define GAME_PROJECT_H

/* ----------------------------------- Local -------------------------------- */
#include "project/project.h"
/* -------------------------------------------------------------------------- */

class GameProject : public Project
{
  Q_OBJECT

public:
  static std::unique_ptr<GameProject> create();

public:
  ~GameProject() override;

protected:
  explicit GameProject(QObject* parent = nullptr);
};

#endif //GAME_PROJECT_H
