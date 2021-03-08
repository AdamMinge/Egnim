#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <list>
/* -------------------------------------------------------------------------- */

class b2World;

namespace egnim::physics
{

  class PhysicsBody;

  class PhysicsWorld
  {
    friend PhysicsBody;

  public:
    explicit PhysicsWorld(const sf::Vector2f& gravity);
    ~PhysicsWorld();

    void update(float time_step, int32_t velocity_iterations, int32_t position_iterations);

    void setGravity(const sf::Vector2f& gravity);
    [[nodiscard]] sf::Vector2f getGravity() const;

  private:
    b2Body* createBody(const b2BodyDef* b2_body_def);
    void destroyBody(b2Body* b2_body);

    std::list<PhysicsBody*> getPhysicsBody();

  private:
    std::unique_ptr<b2World> m_b2_world;
  };

} // namespace egnim::physics

#endif //PHYSICS_WORLD_H
