#ifndef PHYSICS_AABB_H
#define PHYSICS_AABB_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

class b2AABB;

namespace egnim::physics
{

  class PhysicsWorld;

  class EGNIM_UTILITY_API PhysicsAABB
  {
    friend PhysicsWorld;

  public:
    explicit PhysicsAABB(const sf::Vector2f& lower_bound, const sf::Vector2f& upper_bound);
    ~PhysicsAABB();

    void setLowerBound(const sf::Vector2f& lower_bound);
    [[nodiscard]] sf::Vector2f getLowerBound() const;

    void setUpperBound(const sf::Vector2f& upper_bound);
    [[nodiscard]] sf::Vector2f getUpperBound() const;

    [[nodiscard]] bool isValid() const;
    [[nodiscard]] float getPerimeter() const;

    void combine(const PhysicsAABB& aabb);
    void combine(const PhysicsAABB& first_aabb, const PhysicsAABB& second_aabb);

    [[nodiscard]] bool contains(const PhysicsAABB& aabb);

  private:
    [[nodiscard]] b2AABB& getInternalAABB();
    [[nodiscard]] const b2AABB& getInternalAABB() const;

  private:
    std::unique_ptr<b2AABB> m_b2_aabb;
  };

} // namespace egnim::physics

#endif //PHYSICS_AABB_H
