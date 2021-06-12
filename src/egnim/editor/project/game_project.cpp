/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/game_project.h>
/* -------------------------------------------------------------------------- */

std::unique_ptr<GameProject> GameProject::create(const QString& file_name)
{
  auto project = std::unique_ptr<GameProject>(new GameProject(file_name));
  project->save(file_name);
  return project;
}

GameProject::GameProject(QString file_name, QObject* parent) :
  Project(Type::Game, std::move(file_name), parent)
{

}

GameProject::~GameProject() = default;
