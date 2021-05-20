/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_mass.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

PhysicsMass::PhysicsMass() :
  m_mass(0.f),
  m_center(sf::Vector2f(0, 0)),
  m_inertia(0.f)
{

}

PhysicsMass::~PhysicsMass() = default;

void PhysicsMass::setMass(float mass)
{
  m_mass = mass;
}

float PhysicsMass::getMass() const
{
  return m_mass;
}

void PhysicsMass::setCenter(const sf::Vector2f& center)
{
  m_center = center;
}

const sf::Vector2f& PhysicsMass::getCenter() const
{
  return m_center;
}

void PhysicsMass::setRotationalInertia(float inertia)
{
  m_inertia = inertia;
}

float PhysicsMass::getRotationalInertia() const
{
  return m_inertia;
}

} // namespace egnim::physics