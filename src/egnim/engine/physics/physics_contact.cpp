/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_contact.h>
#include <egnim/engine/physics/physics_shape.h>
/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_contact.h>
/* -------------------------------------------------------------------------- */


namespace egnim::physics
{

/* ------------------------------- PhysicsContactImpulse -------------------- */

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

PhysicsManifold::PhysicsManifold(Type type, const sf::Vector2f& local_point, const sf::Vector2f& local_normal,
                                 std::list<PhysicsManifoldPoint> points) :
  m_type(type),
  m_local_point(local_point),
  m_local_normal(local_normal),
  m_points(std::move(points))
{

}

void PhysicsManifold::setLocalPoint(const sf::Vector2f& local_point)
{
  m_local_point.x = local_point.x;
  m_local_point.y = local_point.y;
}

sf::Vector2f PhysicsManifold::getLocalPoint() const
{
  return sf::Vector2f(m_local_point.x, m_local_point.y);
}

void PhysicsManifold::setLocalNormal(const sf::Vector2f& local_normal)
{
  m_local_normal.x = local_normal.x;
  m_local_normal.y = local_normal.y;
}

sf::Vector2f PhysicsManifold::getLocalNormal() const
{
  return sf::Vector2f(m_local_normal.x, m_local_normal.y);
}

void PhysicsManifold::setPoints(const std::list<PhysicsManifoldPoint>& points)
{
  m_points = points;
}

const std::list<PhysicsManifoldPoint>& PhysicsManifold::getPoints() const
{
  return m_points;
}

void PhysicsManifold::setType(Type type)
{
  m_type = type;
}

PhysicsManifold::Type PhysicsManifold::getType() const
{
  return m_type;
}

/* --------------------------------- PhysicsContact ------------------------- */

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