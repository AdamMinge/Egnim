/* ------------------------------------ Qt ---------------------------------- */
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "project/priv/json_project_serializer_impl.h"
#include "project/game_project.h"
#include "document/document_serializer.h"
#include "document/document.h"
/* -------------------------------------------------------------------------- */

namespace priv {

JsonProjectSerializerImpl::JsonProjectSerializerImpl() = default;

JsonProjectSerializerImpl::~JsonProjectSerializerImpl() = default;

QByteArray JsonProjectSerializerImpl::serializeGameProject(const GameProject& project) const
{
  DocumentSerializer document_serializer;
  QJsonArray game_project_documents;
  for(auto& document : project.getDocuments())
  {
    auto document_file_name = document->getFileName();
    if(QFileInfo::exists(document_file_name))
      game_project_documents.append(document_file_name);
  }

  QJsonObject game_project_object;
  game_project_object["type"] = static_cast<int>(project.getType());
  game_project_object["documents"] = game_project_documents;

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

  DocumentSerializer document_serializer;
  auto project_documents = project_object["documents"].toArray();
  for(auto project_document : project_documents)
  {
    auto document = Document::load(project_document.toString());
    if(document)
      game_project->addDocument(std::move(document));
  }

  return game_project;
}

} // namespace priv

