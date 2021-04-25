#ifndef PHYSICS_MANIFOLD_POINT_H
#define PHYSICS_MANIFOLD_POINT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics
{

  class EGNIM_UTILITY_API PhysicsManifoldPoint
  {
  public:
    explicit PhysicsManifoldPoint(sf::Vector2f local_point, float normal_impulse, float tangent_impulse);
    ~PhysicsManifoldPoint();

    void setLocalPoint(const sf::Vector2f& local_point);
    [[nodiscard]] const sf::Vector2f& getLocalPoint() const;

    void setNormalImpulse(float impulse);
    [[nodiscard]] float getNormalImpulse() const;

    void setTangentImpulse(float impulse);
    [[nodiscard]] float getTangentImpulse() const;

  private:
    sf::Vector2f m_local_point;
    float m_normal_impulse;
    float m_tangent_impulse;
  };

} // namespace egnim::physics

#endif //PHYSICS_MANIFOLD_POINT_H
