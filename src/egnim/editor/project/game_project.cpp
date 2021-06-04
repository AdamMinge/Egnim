/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/game_project.h>
/* -------------------------------------------------------------------------- */

std::unique_ptr<GameProject> GameProject::create(QString file_name)
{
  auto project = std::unique_ptr<GameProject>(new GameProject(std::move(file_name)));
  project->save();

  return project;
}

std::unique_ptr<GameProject> GameProject::load(QString file_name)
{
  // TODO : implementation //
  return nullptr;
}

GameProject::GameProject(QString file_name, QObject* parent) :
  Project(Type::Game, std::move(file_name), parent)
{

}

GameProject::~GameProject() = default;

const QDateTime& GameProject::getLastModified() const
{
  return m_last_modified;
}

bool GameProject::save()
{
  // TODO : save implementation //

  m_last_modified = QFileInfo(getFileName()).lastModified();

  Q_EMIT saved();
  return true;
}

