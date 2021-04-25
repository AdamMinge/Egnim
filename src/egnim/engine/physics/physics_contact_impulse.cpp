/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_contact_impulse.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

PhysicsContactImpulse::PhysicsContactImpulse(std::list<float> normal_impulses, std::list<float> tangent_impulses) :
  m_normal_impulses(std::move(normal_impulses)),
  m_tangent_impulses(std::move(tangent_impulses))
{

}

PhysicsContactImpulse::~PhysicsContactImpulse() = default;

void PhysicsContactImpulse::setNormalImpulses(std::list<float> normal_impulses)
{
  m_normal_impulses = std::move(normal_impulses);
}

const std::list<float>& PhysicsContactImpulse::getNormalImpulses() const
{
  return m_normal_impulses;
}

void PhysicsContactImpulse::setTangentImpulses(std::list<float> tangent_impulses)
{
  m_tangent_impulses = std::move(tangent_impulses);
}

const std::list<float>& PhysicsContactImpulse::getTangentImpulses() const
{
  return m_tangent_impulses;
}

} // namespace egnim::physics
