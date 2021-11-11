/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/project/priv/project_serializer_impl.h"
#include "egnim/tools/editor/project/game_project.h"
/* ----------------------------------- Engine ------------------------------- */
#include <egnim/engine/core/unique_pointer.h>
/* -------------------------------------------------------------------------- */

namespace priv {

ProjectSerializerImpl::ProjectSerializerImpl() = default;

ProjectSerializerImpl::~ProjectSerializerImpl() = default;

QByteArray ProjectSerializerImpl::serialize(const Project& project) const
{
  if(auto game_project = dynamic_cast<const GameProject*>(std::addressof(project)); game_project)
    return serializeGameProject(*game_project);

  return QByteArray{};
}

std::unique_ptr<Project> ProjectSerializerImpl::deserialize(const QByteArray& array) const
{
  if(auto game_project = deserializeGameProject(array); game_project)
    return game_project;

  return nullptr;
}

} // namespace priv

