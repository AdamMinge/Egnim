/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_mass_info.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

PhysicsMassInfo::PhysicsMassInfo() :
  m_mass(0.f),
  m_center(sf::Vector2f(0, 0)),
  m_inertia(0.f)
{

}

PhysicsMassInfo::~PhysicsMassInfo() = default;

void PhysicsMassInfo::setMass(float mass)
{
  m_mass = mass;
}

float PhysicsMassInfo::getMass() const
{
  return m_mass;
}

void PhysicsMassInfo::setCenter(const sf::Vector2f& center)
{
  m_center = center;
}

const sf::Vector2f& PhysicsMassInfo::getCenter() const
{
  return m_center;
}

void PhysicsMassInfo::setRotationalInertia(float inertia)
{
  m_inertia = inertia;
}

float PhysicsMassInfo::getRotationalInertia() const
{
  return m_inertia;
}

} // namespace egnim::physics