/* ------------------------------------ Qt ---------------------------------- */
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/document/priv/json_document_serializer_impl.h"
#include "egnim/tools/editor/document/scene_document.h"
/* -------------------------------------------------------------------------- */

namespace priv {

JsonDocumentSerializerImpl::JsonDocumentSerializerImpl() = default;

JsonDocumentSerializerImpl::~JsonDocumentSerializerImpl() = default;

QByteArray JsonDocumentSerializerImpl::serializeSceneDocument(const SceneDocument& document) const
{
  QJsonObject scene_document_object;
  scene_document_object["type"] = static_cast<int>(document.getType());

  QJsonDocument save_game_project(scene_document_object);
  return save_game_project.toJson(QJsonDocument::Compact);
}

std::unique_ptr<SceneDocument> JsonDocumentSerializerImpl::deserializeSceneDocument(const QByteArray& array) const
{
  auto load_document = QJsonDocument::fromJson(array);

  if(load_document.isNull())
    return nullptr;

  auto document_object = load_document.object();
  auto document_type = document_object["type"];

  if(document_type.type() != QJsonValue::Double || document_type != static_cast<int>(Document::Type::Scene))
    return nullptr;

  auto scene_document = SceneDocument::create();
  return scene_document;
}

} // namespace priv

