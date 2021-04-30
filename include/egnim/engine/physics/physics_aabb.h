#ifndef PHYSICS_AABB_H
#define PHYSICS_AABB_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */


namespace egnim::physics
{

  class EGNIM_UTILITY_API PhysicsAABB
  {
  public:
    explicit PhysicsAABB(const sf::Vector2f& lower_bound, const sf::Vector2f& upper_bound);
    ~PhysicsAABB();

    [[nodiscard]] sf::Vector2f getCenter() const;
    [[nodiscard]] sf::Vector2f getExtents() const;

    void setLowerBound(const sf::Vector2f& lower_bound);
    [[nodiscard]] const sf::Vector2f& getLowerBound() const;

    void setUpperBound(const sf::Vector2f& upper_bound);
    [[nodiscard]] const sf::Vector2f& getUpperBound() const;

    [[nodiscard]] bool isValid() const;
    [[nodiscard]] float getPerimeter() const;

    void combine(const PhysicsAABB& aabb);
    void combine(const PhysicsAABB& first_aabb, const PhysicsAABB& second_aabb);

    [[nodiscard]] bool contains(const PhysicsAABB& aabb) const;

  private:
    sf::Vector2f m_lower_bound;
    sf::Vector2f m_upper_bound;
  };

} // namespace egnim::physics

#endif //PHYSICS_AABB_H
