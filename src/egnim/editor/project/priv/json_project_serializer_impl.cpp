/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/priv/json_project_serializer_impl.h>
#include <egnim/editor/project/game_project.h>
/* -------------------------------------------------------------------------- */

namespace priv {

JsonProjectSerializerImpl::JsonProjectSerializerImpl() = default;

JsonProjectSerializerImpl::~JsonProjectSerializerImpl() = default;

QByteArray JsonProjectSerializerImpl::serializeGameProject(const GameProject& project) const
{
  // TODO : implementation //
  return QByteArray();
}

std::unique_ptr<GameProject> JsonProjectSerializerImpl::deserializeGameProject(const QByteArray& array) const
{
  // TODO : implementation //
  return nullptr;
}

} // namespace priv

