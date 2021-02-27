#ifndef PHYSICS_WORLD_IMPL_H
#define PHYSICS_WORLD_IMPL_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_world.h>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

namespace egnim::physics::priv
{

  class WorldImpl
  {
  public:
    explicit WorldImpl(const sf::Vector2f& gravity);
    ~WorldImpl();

    void update(float time_step, int32_t velocity_iterations, int32_t position_iterations);

    void setGravity(const sf::Vector2f& gravity);
    [[nodiscard]] sf::Vector2f getGravity() const;

  private:
    std::unique_ptr<b2World> m_world;
  };

} // namespace egnim::physics::priv

#endif //PHYSICS_WORLD_IMPL_H
