/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/priv/physics_world_impl.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics::priv {

WorldImpl::WorldImpl(const sf::Vector2f& gravity) :
  m_world(std::make_unique<b2World>(b2Vec2(gravity.x, gravity.y)))
{

}

WorldImpl::~WorldImpl() = default;

void WorldImpl::update(float time_step, int32_t velocity_iterations, int32_t position_iterations)
{
  m_world->Step(time_step, velocity_iterations, position_iterations);
}

void WorldImpl::setGravity(const sf::Vector2f& gravity)
{
  m_world->SetGravity(b2Vec2(gravity.x, gravity.y));
}

sf::Vector2f WorldImpl::getGravity() const
{
  auto b2_gravity = m_world->GetGravity();
  return sf::Vector2f(b2_gravity.x, b2_gravity.y);
}

} // namespace egnim::physics::priv