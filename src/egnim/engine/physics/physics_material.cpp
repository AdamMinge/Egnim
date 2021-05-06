/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_material.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

[[maybe_unused]] const PhysicsMaterial PhysicsMaterial::DefaultMaterial = PhysicsMaterial(1.0f, 0.5f, 0.5f, 0.5f);

PhysicsMaterial::PhysicsMaterial(float density, float restitution, float friction, float threshold) noexcept :
  m_density(density),
  m_restitution(restitution),
  m_friction(friction),
  m_restitution_threshold(threshold)
{

}

void PhysicsMaterial::setDensity(float density)
{
  m_density = density;
}

void PhysicsMaterial::setRestitution(float restitution)
{
  m_restitution = restitution;
}

void PhysicsMaterial::setFriction(float friction)
{
  m_friction = friction;
}

void PhysicsMaterial::setRestitutionThreshold(float threshold)
{
  m_restitution_threshold = threshold;
}

float PhysicsMaterial::getDensity() const
{
  return m_density;
}

float PhysicsMaterial::getRestitution() const
{
  return m_restitution;
}

float PhysicsMaterial::getFriction() const
{
  return m_friction;
}

float PhysicsMaterial::getRestitutionThreshold() const
{
  return m_restitution_threshold;
}

} // namespace egnim::physics