/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_math.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_aabb.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

PhysicsAABB::PhysicsAABB(const sf::Vector2f& lower_bound, const sf::Vector2f& upper_bound) :
  m_lower_bound(lower_bound),
  m_upper_bound(upper_bound)
{

}

PhysicsAABB::~PhysicsAABB() = default;

sf::Vector2f PhysicsAABB::getCenter() const
{
  return 0.5f * (m_lower_bound + m_upper_bound);
}

sf::Vector2f PhysicsAABB::getExtents() const
{
  return 0.5f * (m_upper_bound - m_lower_bound);
}

void PhysicsAABB::setLowerBound(const sf::Vector2f& lower_bound)
{
  m_lower_bound = lower_bound;
}

const sf::Vector2f& PhysicsAABB::getLowerBound() const
{
  return m_lower_bound;
}

void PhysicsAABB::setUpperBound(const sf::Vector2f& upper_bound)
{
  m_upper_bound = upper_bound;
}

const sf::Vector2f& PhysicsAABB::getUpperBound() const
{
  return m_upper_bound;
}

bool PhysicsAABB::isValid() const
{
  return m_lower_bound.x <= m_upper_bound.x && m_lower_bound.y <= m_upper_bound.y;
}

float PhysicsAABB::getPerimeter() const
{
  auto w = m_upper_bound - m_lower_bound;
  return 2.0f * (w.x + w.y);
}

void PhysicsAABB::combine(const PhysicsAABB& aabb)
{
  combine(*this, aabb);
}

void PhysicsAABB::combine(const PhysicsAABB& first_aabb, const PhysicsAABB& second_aabb)
{
  setLowerBound(sf::Vector2f(
    std::min(first_aabb.getLowerBound().x, second_aabb.getLowerBound().x),
    std::min(first_aabb.getLowerBound().y, second_aabb.getLowerBound().y)));

  setUpperBound(sf::Vector2f(
    std::min(first_aabb.getUpperBound().x, second_aabb.getUpperBound().x),
    std::min(first_aabb.getUpperBound().y, second_aabb.getUpperBound().y)));
}

bool PhysicsAABB::contains(const PhysicsAABB& aabb) const
{
  auto result = true;
  result &= getLowerBound().x <= aabb.getLowerBound().x;
  result &= getLowerBound().y <= aabb.getLowerBound().y;
  result &= aabb.getUpperBound().x <= getUpperBound().x;
  result &= aabb.getUpperBound().y <= getUpperBound().y;
  return result;
}

} // namespace egnim::physics
