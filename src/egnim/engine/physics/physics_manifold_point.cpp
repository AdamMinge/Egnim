/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_manifold_point.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

PhysicsManifoldPoint::PhysicsManifoldPoint(sf::Vector2f local_point, float normal_impulse, float tangent_impulse) :
  m_local_point(local_point),
  m_normal_impulse(normal_impulse),
  m_tangent_impulse(tangent_impulse)
{

}

PhysicsManifoldPoint::~PhysicsManifoldPoint() = default;

void PhysicsManifoldPoint::setLocalPoint(const sf::Vector2f& local_point)
{
  m_local_point = local_point;
}

const sf::Vector2f& PhysicsManifoldPoint::getLocalPoint() const
{
  return m_local_point;
}

void PhysicsManifoldPoint::setNormalImpulse(float impulse)
{
  m_normal_impulse = impulse;
}

float PhysicsManifoldPoint::getNormalImpulse() const
{
  return m_normal_impulse;
}

void PhysicsManifoldPoint::setTangentImpulse(float impulse)
{
  m_tangent_impulse = impulse;
}

float PhysicsManifoldPoint::getTangentImpulse() const
{
  return m_tangent_impulse;
}

} // namespace egnim::physics