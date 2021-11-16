#ifndef PROJECT_SERIALIZER_IMPL_H
#define PROJECT_SERIALIZER_IMPL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QByteArray>
/* -------------------------------------------------------------------------- */

class GameProject;
class Project;

namespace priv
{

  class ProjectSerializerImpl
  {
  public:
    ProjectSerializerImpl();
    virtual ~ProjectSerializerImpl();

    [[nodiscard]] QByteArray serialize(const Project& project) const;
    [[nodiscard]] std::unique_ptr<Project> deserialize(const QByteArray& array) const;

  protected:
    [[nodiscard]] virtual QByteArray serializeGameProject(const GameProject& project) const = 0;
    [[nodiscard]] virtual std::unique_ptr<GameProject> deserializeGameProject(const QByteArray& array) const = 0;
  };

} // namespace priv


#endif //PROJECT_SERIALIZER_IMPL_H
