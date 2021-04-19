/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_contact.h>
#include <egnim/engine/physics/physics_shape.h>
/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_contact.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* -------------------------------------------------------------------------- */


namespace egnim::physics
{

/* ------------------------------- PhysicsManifoldPoint --------------------- */

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

/* --------------------------------- PhysicsManifold ------------------------ */

PhysicsManifold::~PhysicsManifold() = default;

PhysicsManifold::PhysicsManifold(b2Manifold* manifold) :
  m_manifold(manifold)
{

}

void PhysicsManifold::setLocalPoint(const sf::Vector2f& local_point)
{
  assert(m_manifold);
  m_manifold->localPoint.x = local_point.x;
  m_manifold->localPoint.y = local_point.y;
}

sf::Vector2f PhysicsManifold::getLocalPoint() const
{
  assert(m_manifold);
  return sf::Vector2f(m_manifold->localPoint.x, m_manifold->localPoint.y);
}

void PhysicsManifold::setLocalNormal(const sf::Vector2f& local_normal)
{
  assert(m_manifold);
  m_manifold->localNormal.x = local_normal.x;
  m_manifold->localNormal.y = local_normal.y;
}

sf::Vector2f PhysicsManifold::getLocalNormal() const
{
  assert(m_manifold);
  return sf::Vector2f(m_manifold->localNormal.x, m_manifold->localNormal.y);
}

void PhysicsManifold::setPoints(const std::list<PhysicsManifoldPoint>& points)
{
  assert(m_manifold);
  assert(points.size() <= b2_maxManifoldPoints);

  m_manifold->pointCount = static_cast<int32>(points.size());
  auto current_point_id = 0;
  for(auto& point : points)
  {
    m_manifold->points[current_point_id].localPoint.x = point.getLocalPoint().x;
    m_manifold->points[current_point_id].localPoint.y = point.getLocalPoint().y;
    m_manifold->points[current_point_id].tangentImpulse = point.getTangentImpulse();
    m_manifold->points[current_point_id].normalImpulse = point.getNormalImpulse();

    current_point_id += 1;
  }
}

std::list<PhysicsManifoldPoint> PhysicsManifold::getPoints() const
{
  assert(m_manifold);
  std::list<PhysicsManifoldPoint> points;
  for(auto i = 0; i < m_manifold->pointCount; ++i)
    points.emplace_back(PhysicsManifoldPoint(
      sf::Vector2f(m_manifold->points[i].localPoint.x, m_manifold->points[i].localPoint.y),
      m_manifold->points[i].normalImpulse, m_manifold->points[i].tangentImpulse));
  return points;
}

void PhysicsManifold::setType(Type type)
{
  assert(m_manifold);
  m_manifold->type = static_cast<b2Manifold::Type>(type);
}

PhysicsManifold::Type PhysicsManifold::getType() const
{
  assert(m_manifold);
  return static_cast<Type>(m_manifold->type);
}

/* --------------------------------- PhysicsContact ------------------------- */

PhysicsContact::~PhysicsContact() = default;

PhysicsContact::PhysicsContact(b2Contact *b2_contact) :
  m_b2_contact(b2_contact),
  m_physics_manifold(m_b2_contact->GetManifold())
{

}

PhysicsShape* PhysicsContact::getFirstShape()
{
  assert(m_b2_contact);
  return reinterpret_cast<PhysicsShape*>(m_b2_contact->GetFixtureA()->GetUserData().pointer);
}

const PhysicsShape* PhysicsContact::getFirstShape() const
{
  assert(m_b2_contact);
  return reinterpret_cast<const PhysicsShape*>(m_b2_contact->GetFixtureA()->GetUserData().pointer);
}

PhysicsShape* PhysicsContact::getSecondShape()
{
  assert(m_b2_contact);
  return reinterpret_cast<PhysicsShape*>(m_b2_contact->GetFixtureB()->GetUserData().pointer);
}

const PhysicsShape* PhysicsContact::getSecondShape() const
{
  assert(m_b2_contact);
  return reinterpret_cast<const PhysicsShape*>(m_b2_contact->GetFixtureB()->GetUserData().pointer);
}

PhysicsManifold* PhysicsContact::getPhysicsManifold()
{
  return std::addressof(m_physics_manifold);
}

const PhysicsManifold* PhysicsContact::getPhysicsManifold() const
{
  return std::addressof(m_physics_manifold);
}

bool PhysicsContact::isTouching() const
{
  assert(m_b2_contact);
  return m_b2_contact->IsTouching();
}

void PhysicsContact::setEnabled(bool enable)
{
  assert(m_b2_contact);
  m_b2_contact->SetEnabled(enable);
}

bool PhysicsContact::isEnabled() const
{
  assert(m_b2_contact);
  return m_b2_contact->IsEnabled();
}

void PhysicsContact::setFriction(float friction)
{
  assert(m_b2_contact);
  m_b2_contact->SetFriction(friction);
}

float PhysicsContact::getFriction() const
{
  assert(m_b2_contact);
  return m_b2_contact->GetFriction();
}

void PhysicsContact::resetFriction()
{
  assert(m_b2_contact);
  m_b2_contact->ResetFriction();
}

void PhysicsContact::setRestitution(float restitution)
{
  assert(m_b2_contact);
  m_b2_contact->SetRestitution(restitution);
}

float PhysicsContact::getRestitution() const
{
  assert(m_b2_contact);
  return m_b2_contact->GetRestitution();
}

void PhysicsContact::resetRestitution()
{
  assert(m_b2_contact);
  m_b2_contact->ResetRestitution();
}

void PhysicsContact::setRestitutionThreshold(float threshold)
{
  assert(m_b2_contact);
  m_b2_contact->SetRestitutionThreshold(threshold);
}

float PhysicsContact::getRestitutionThreshold() const
{
  assert(m_b2_contact);
  return m_b2_contact->GetRestitutionThreshold();
}

void PhysicsContact::resetRestitutionThreshold()
{
  assert(m_b2_contact);
  m_b2_contact->ResetRestitutionThreshold();
}

void PhysicsContact::setTangentSpeed(float speed)
{
  assert(m_b2_contact);
  m_b2_contact->SetTangentSpeed(speed);
}

float PhysicsContact::getTangentSpeed() const
{
  assert(m_b2_contact);
  return m_b2_contact->GetTangentSpeed();
}

} // namespace egnim::physics