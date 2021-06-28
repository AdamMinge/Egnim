/* ----------------------------------- Local -------------------------------- */
#include "project/project_serializer.h"
#include "project/project.h"
#include "project/priv/json_project_serializer_impl.h"
/* -------------------------------------------------------------------------- */

ProjectSerializer::ProjectSerializer() = default;
ProjectSerializer::~ProjectSerializer() = default;

QByteArray ProjectSerializer::serialize(const Project& project, Format format) const
{
  auto impl = getImpl(format);
  Q_ASSERT(impl);

  return impl->serialize(project);
}

std::unique_ptr<Project> ProjectSerializer::deserialize(const QByteArray& array, Format format) const
{
  auto impl = getImpl(format);
  Q_ASSERT(impl);

  return impl->deserialize(array);
}

std::unique_ptr<priv::ProjectSerializerImpl> ProjectSerializer::getImpl(Format format) const
{
  switch(format)
  {
    case Format::Json:
      return std::make_unique<priv::JsonProjectSerializerImpl>();
  }

  return nullptr;
}