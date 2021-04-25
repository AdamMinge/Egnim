#ifndef PHYSICS_MATERIAL_H
#define PHYSICS_MATERIAL_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics
{

  class EGNIM_UTILITY_API PhysicsMaterial
  {
    public:
    [[maybe_unused]] static const PhysicsMaterial DefaultMaterial;

    public:
    PhysicsMaterial(float density, float restitution, float friction, float threshold) noexcept;

    void setDensity(float density);
    void setRestitution(float restitution);
    void setFriction(float friction);
    void setRestitutionThreshold(float threshold);

    [[nodiscard]] float getDensity() const;
    [[nodiscard]] float getRestitution() const;
    [[nodiscard]] float getFriction() const;
    [[nodiscard]] float getRestitutionThreshold() const;

    private:
    float m_density;
    float m_restitution;
    float m_friction;
    float m_restitution_threshold;
  };

} // namespace egnim::physics

#endif //PHYSICS_MATERIAL_H
