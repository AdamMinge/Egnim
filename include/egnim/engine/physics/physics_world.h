#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

namespace egnim::physics::priv
{
  class WorldImpl;
}

namespace egnim::physics
{

  class World
  {
  public:
    explicit World(const sf::Vector2f& gravity);
    ~World();

    void update(float time_step, int32_t velocity_iterations, int32_t position_iterations);

    void setGravity(const sf::Vector2f& gravity);
    [[nodiscard]] sf::Vector2f getGravity() const;

  private:
    std::unique_ptr<priv::WorldImpl> m_impl;
  };

} // namespace egnim::physics

#endif //PHYSICS_WORLD_H
