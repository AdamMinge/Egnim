#ifndef PHYSICS_MASS_INFO_H
#define PHYSICS_MASS_INFO_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics
{

  class EGNIM_UTILITY_API PhysicsMassInfo
  {
  public:
    explicit PhysicsMassInfo();
    ~PhysicsMassInfo();

    void setMass(float mass);
    [[nodiscard]] float getMass() const;

    void setCenter(const sf::Vector2f& center);
    [[nodiscard]] const sf::Vector2f& getCenter() const;

    void setRotationalInertia(float inertia);
    [[nodiscard]] float getRotationalInertia() const;

  private:
    float m_mass;
    sf::Vector2f m_center;
    float m_inertia;
  };

} // namespace egnim::physics

#endif //PHYSICS_MASS_INFO_H
