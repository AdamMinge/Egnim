#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/scene/component.h>
/* -------------------------------------------------------------------------- */

class b2Body;
struct b2BodyDef;

namespace egnim::physics
{

  class PhysicsWorld;

  class PhysicsBody : public scene::Component
  {
    friend PhysicsWorld;

  public:
    explicit PhysicsBody(PhysicsWorld& physics_world);
    ~PhysicsBody() override;

    void setPosition(const sf::Vector2f& position);
    [[nodiscard]] sf::Vector2f getPosition() const;

    void setRotation(float angle);
    [[nodiscard]] float getRotation() const;

    void update(sf::Time dt) override;

    [[nodiscard]] PhysicsWorld& getPhysicsWorld();
    [[nodiscard]] const PhysicsWorld& getPhysicsWorld() const;

  protected:
    void createBody(const b2BodyDef& b2_body_def);
    void destroyBody();

  private:
    void beforeSimulation();
    void afterSimulation();

  private:
    PhysicsWorld& m_physics_world;
    b2Body* m_b2_body;
  };

}

#endif //PHYSICS_BODY_H
