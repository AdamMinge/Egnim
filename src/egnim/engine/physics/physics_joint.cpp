/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_joint.h>
#include <egnim/engine/physics/physics_body.h>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <cassert>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

PhysicsJoint::PhysicsJoint(Type type, PhysicsBody& first_physics_body, PhysicsBody& second_physics_body) :
  m_type(type),
  m_physics_world(*first_physics_body.getPhysicsWorld()),
  m_first_physics_body(first_physics_body),
  m_second_physics_body(second_physics_body)
{
  assert(first_physics_body.getPhysicsWorld() == second_physics_body.getPhysicsWorld());
}

PhysicsJoint::~PhysicsJoint() = default;

const PhysicsBody* PhysicsJoint::getFirstPhysicsBody() const
{
  return std::addressof(m_first_physics_body);
}

PhysicsBody* PhysicsJoint::getFirstPhysicsBody()
{
  return std::addressof(m_first_physics_body);
}

const PhysicsBody* PhysicsJoint::getSecondPhysicsBody() const
{
  return std::addressof(m_second_physics_body);
}

PhysicsBody* PhysicsJoint::getSecondPhysicsBody()
{
  return std::addressof(m_second_physics_body);
}

const PhysicsWorld* PhysicsJoint::getPhysicsWorld() const
{
  return std::addressof(m_physics_world);
}

PhysicsWorld* PhysicsJoint::getPhysicsWorld()
{
  return std::addressof(m_physics_world);
}

PhysicsJoint::Type PhysicsJoint::getType() const
{
  return m_type;
}

} // namespace egnim::physics