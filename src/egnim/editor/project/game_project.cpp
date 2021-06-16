/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/game_project.h>
/* -------------------------------------------------------------------------- */

std::unique_ptr<GameProject> GameProject::create()
{
  auto project = std::unique_ptr<GameProject>(new GameProject());
  return project;
}

GameProject::GameProject(QObject* parent) :
  Project(Type::Game, parent)
{

}

GameProject::~GameProject() = default;
