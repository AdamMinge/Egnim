/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_contact.h>
#include <egnim/engine/physics/physics_shape.h>
/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_contact.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics
{

PhysicsContact::~PhysicsContact() = default;

PhysicsContact::PhysicsContact(PhysicsShape* first_shape, PhysicsShape* second_shape, const PhysicsManifold& physics_manifold) :
  m_first_shape(first_shape),
  m_second_shape(second_shape),
  m_physics_manifold(physics_manifold),
  m_touching(true),
  m_enabled(true),
  m_friction(b2MixFriction(first_shape->getFriction(), second_shape->getFriction())),
  m_restitution(b2MixRestitution(first_shape->getRestitution(), second_shape->getRestitution())),
  m_threshold(b2MixRestitutionThreshold(first_shape->getRestitutionThreshold(), second_shape->getRestitutionThreshold())),
  m_speed(0)
{

}

PhysicsShape* PhysicsContact::getFirstShape()
{
  return m_first_shape;
}

const PhysicsShape* PhysicsContact::getFirstShape() const
{
  return m_first_shape;
}

PhysicsShape* PhysicsContact::getSecondShape()
{
  return m_second_shape;
}

const PhysicsShape* PhysicsContact::getSecondShape() const
{
  return m_second_shape;
}

PhysicsManifold* PhysicsContact::getPhysicsManifold()
{
  return std::addressof(m_physics_manifold);
}

const PhysicsManifold* PhysicsContact::getPhysicsManifold() const
{
  return std::addressof(m_physics_manifold);
}

void PhysicsContact::setTouching(bool touching)
{
  m_touching = touching;
}

bool PhysicsContact::isTouching() const
{
  return m_touching;
}

void PhysicsContact::setEnabled(bool enable)
{
  m_enabled = enable;
}

bool PhysicsContact::isEnabled() const
{
  return m_enabled;
}

void PhysicsContact::setFriction(float friction)
{
  m_friction = friction;
}

float PhysicsContact::getFriction() const
{
  return m_friction;
}

void PhysicsContact::resetFriction()
{
  m_friction = b2MixFriction(m_first_shape->getFriction(), m_second_shape->getFriction());
}

void PhysicsContact::setRestitution(float restitution)
{
  m_restitution = restitution;
}

float PhysicsContact::getRestitution() const
{
  return m_restitution;
}

void PhysicsContact::resetRestitution()
{
  m_friction = b2MixFriction(m_first_shape->getRestitution(), m_second_shape->getRestitution());
}

void PhysicsContact::setRestitutionThreshold(float threshold)
{
  m_threshold = threshold;
}

float PhysicsContact::getRestitutionThreshold() const
{
  return m_threshold;
}

void PhysicsContact::resetRestitutionThreshold()
{
  m_friction = b2MixFriction(m_first_shape->getRestitutionThreshold(), m_second_shape->getRestitutionThreshold());
}

void PhysicsContact::setTangentSpeed(float speed)
{
  m_speed = speed;
}

float PhysicsContact::getTangentSpeed() const
{
  return m_speed;
}

} // namespace egnim::physics