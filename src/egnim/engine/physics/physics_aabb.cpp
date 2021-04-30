/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_collision.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_aabb.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

PhysicsAABB::PhysicsAABB(const sf::Vector2f& lower_bound, const sf::Vector2f& upper_bound) :
  m_b2_aabb(std::make_unique<b2AABB>())
{
  setLowerBound(lower_bound);
  setUpperBound(upper_bound);
}

PhysicsAABB::~PhysicsAABB() = default;

void PhysicsAABB::setLowerBound(const sf::Vector2f& lower_bound)
{
  m_b2_aabb->lowerBound = b2Vec2(lower_bound.x, lower_bound.y);
}

sf::Vector2f PhysicsAABB::getLowerBound() const
{
  return sf::Vector2f(m_b2_aabb->lowerBound.x, m_b2_aabb->lowerBound.y);
}

void PhysicsAABB::setUpperBound(const sf::Vector2f& upper_bound)
{
  m_b2_aabb->lowerBound = b2Vec2(upper_bound.x, upper_bound.y);
}

sf::Vector2f PhysicsAABB::getUpperBound() const
{
  return sf::Vector2f(m_b2_aabb->upperBound.x, m_b2_aabb->upperBound.y);
}

bool PhysicsAABB::isValid() const
{
  return m_b2_aabb->IsValid();
}

float PhysicsAABB::getPerimeter() const
{
  return m_b2_aabb->GetPerimeter();
}

void PhysicsAABB::combine(const PhysicsAABB& aabb)
{
  m_b2_aabb->Combine(*aabb.m_b2_aabb);
}

void PhysicsAABB::combine(const PhysicsAABB& first_aabb, const PhysicsAABB& second_aabb)
{
  m_b2_aabb->Combine(*first_aabb.m_b2_aabb, *second_aabb.m_b2_aabb);
}

bool PhysicsAABB::contains(const PhysicsAABB& aabb)
{
  return m_b2_aabb->Contains(*aabb.m_b2_aabb);
}

b2AABB& PhysicsAABB::getInternalAABB()
{
  return *m_b2_aabb;
}

const b2AABB& PhysicsAABB::getInternalAABB() const
{
  return *m_b2_aabb;
}

} // namespace egnim::physics
