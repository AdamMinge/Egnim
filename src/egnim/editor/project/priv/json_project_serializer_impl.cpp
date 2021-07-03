/* ------------------------------------ Qt ---------------------------------- */
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "project/priv/json_project_serializer_impl.h"
#include "project/game_project.h"
/* -------------------------------------------------------------------------- */

namespace priv {

JsonProjectSerializerImpl::JsonProjectSerializerImpl() = default;

JsonProjectSerializerImpl::~JsonProjectSerializerImpl() = default;

QByteArray JsonProjectSerializerImpl::serializeGameProject(const GameProject& project) const
{
  QJsonObject game_project_object;
  game_project_object["type"] = static_cast<int>(project.getType());

  QJsonDocument save_game_project(game_project_object);
  return save_game_project.toJson(QJsonDocument::Compact);
}

std::unique_ptr<GameProject> JsonProjectSerializerImpl::deserializeGameProject(const QByteArray& array) const
{
  auto load_project = QJsonDocument::fromJson(array);

  if(load_project.isNull())
    return nullptr;

  auto project_object = load_project.object();
  auto project_type = project_object["type"];

  if(project_type.type() != QJsonValue::Double || project_type != static_cast<int>(Project::Type::Game))
    return nullptr;

  auto game_project = GameProject::create();
  return game_project;
}

} // namespace priv

