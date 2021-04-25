/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_manifold.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

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

} // namespace egnim::physics