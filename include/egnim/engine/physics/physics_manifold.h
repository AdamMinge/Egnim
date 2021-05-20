#ifndef PHYSICS_MANIFOLD_H
#define PHYSICS_MANIFOLD_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <list>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/physics/physics_manifold_point.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics
{

  class EGNIM_UTILITY_API PhysicsManifold
  {
  public:
    enum class Type;

  public:
    explicit PhysicsManifold(Type type, const sf::Vector2f& local_point, const sf::Vector2f& local_normal,
                             std::list<PhysicsManifoldPoint> points = {});
    ~PhysicsManifold();

    void setLocalPoint(const sf::Vector2f& local_point);
    [[nodiscard]] sf::Vector2f getLocalPoint() const;

    void setLocalNormal(const sf::Vector2f& local_normal);
    [[nodiscard]] sf::Vector2f getLocalNormal() const;

    void setPoints(const std::list<PhysicsManifoldPoint>& points);
    [[nodiscard]] const std::list<PhysicsManifoldPoint>& getPoints() const;

    void setType(Type type);
    [[nodiscard]] Type getType() const;

  private:
    Type m_type;
    sf::Vector2f m_local_point;
    sf::Vector2f m_local_normal;
    std::list<PhysicsManifoldPoint> m_points;
  };

  enum class PhysicsManifold::Type
  {
    CIRCLES,
    FACE_A,
    FACE_B
  };

} // namespace egnim::physics


#endif //PHYSICS_MANIFOLD_H
