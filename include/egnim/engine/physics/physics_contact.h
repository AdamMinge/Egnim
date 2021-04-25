#ifndef PHYSICS_CONTACT_H
#define PHYSICS_CONTACT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/physics/physics_manifold.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics
{

  class PhysicsShape;

  class EGNIM_UTILITY_API PhysicsContact
  {
  public:
    explicit PhysicsContact(PhysicsShape* first_shape, PhysicsShape* second_shape, const PhysicsManifold& physics_manifold);
    ~PhysicsContact();

    [[nodiscard]] PhysicsShape* getFirstShape();
    [[nodiscard]] const PhysicsShape* getFirstShape() const;

    [[nodiscard]] PhysicsShape* getSecondShape();
    [[nodiscard]] const PhysicsShape* getSecondShape() const;

    [[nodiscard]] PhysicsManifold* getPhysicsManifold();
    [[nodiscard]] const PhysicsManifold* getPhysicsManifold() const;

    void setTouching(bool touching);
    [[nodiscard]] bool isTouching() const;

    void setEnabled(bool enable);
    [[nodiscard]] bool isEnabled() const;

    void setFriction(float friction);
    [[nodiscard]] float getFriction() const;
    void resetFriction();

    void setRestitution(float restitution);
    [[nodiscard]] float getRestitution() const;
    void resetRestitution();

    void setRestitutionThreshold(float threshold);
    [[nodiscard]] float getRestitutionThreshold() const;
    void resetRestitutionThreshold();

    void setTangentSpeed(float speed);
    [[nodiscard]] float getTangentSpeed() const;

  private:
    PhysicsShape* m_first_shape;
    PhysicsShape* m_second_shape;
    PhysicsManifold m_physics_manifold;
    bool m_touching;
    bool m_enabled;
    float m_friction;
    float m_restitution;
    float m_threshold;
    float m_speed;
  };

} // namespace egnim::physics

#endif //PHYSICS_CONTACT_H
