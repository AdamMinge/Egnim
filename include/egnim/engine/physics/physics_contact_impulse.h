#ifndef PHYSICS_CONTACT_IMPULSE_H
#define PHYSICS_CONTACT_IMPULSE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <list>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics
{

  class EGNIM_UTILITY_API PhysicsContactImpulse
  {
  public:
    explicit PhysicsContactImpulse(std::list<float> normal_impulses, std::list<float> tangent_impulses);
    ~PhysicsContactImpulse();

    void setNormalImpulses(std::list<float> normal_impulses);
    [[nodiscard]] const std::list<float>& getNormalImpulses() const;

    void setTangentImpulses(std::list<float> tangent_impulses);
    [[nodiscard]] const std::list<float>& getTangentImpulses() const;

  private:
    std::list<float> m_normal_impulses;
    std::list<float> m_tangent_impulses;
  };

} // namespace egnim::physics

#endif //PHYSICS_CONTACT_IMPULSE_H
