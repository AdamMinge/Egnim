#ifndef PROJECT_SERIALIZER_H
#define PROJECT_SERIALIZER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QByteArray>
/* -------------------------------------------------------------------------- */

class Project;

namespace priv
{
  class ProjectSerializerImpl;
}

class ProjectSerializer
{
public:
  enum class Format
  {
    Json,
  };

public:
  ProjectSerializer();
  ~ProjectSerializer();

  [[nodiscard]] QByteArray serialize(const Project& project, Format format = Format::Json) const;
  [[nodiscard]] std::unique_ptr<Project> deserialize(const QByteArray& array, Format format = Format::Json) const;

private:
  [[nodiscard]] std::unique_ptr<priv::ProjectSerializerImpl> getImpl(Format format) const;
};

#endif //PROJECT_SERIALIZER_H
