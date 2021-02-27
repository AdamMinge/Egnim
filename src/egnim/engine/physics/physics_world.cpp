/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/physics/priv/physics_world_impl.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

World::World(const sf::Vector2f& gravity) :
  m_impl(std::make_unique<priv::WorldImpl>(gravity))
{

}

World::~World() = default;

void World::update(float time_step, int32_t velocity_iterations, int32_t position_iterations)
{
  m_impl->update(time_step, velocity_iterations, position_iterations);
}

void World::setGravity(const sf::Vector2f& gravity)
{
  m_impl->setGravity(gravity);
}

sf::Vector2f World::getGravity() const
{
  return m_impl->getGravity();
}

} // namespace egnim::physics
