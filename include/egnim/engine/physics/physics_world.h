#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <list>
/* -------------------------------------------------------------------------- */

class b2World;
struct b2BodyDef;

class b2Joint;
struct b2JointDef;

namespace egnim::scene
{

  class SceneNode;

}

namespace egnim::physics
{

  class PhysicsBody;
  class PhysicsJoint;

  class PhysicsWorld
  {
    friend PhysicsBody;
    friend PhysicsJoint;

  public:
    explicit PhysicsWorld(scene::SceneNode& scene_node, const sf::Vector2f& gravity);
    ~PhysicsWorld();

    void update(float time_step, int32_t velocity_iterations, int32_t position_iterations);

    void setGravity(const sf::Vector2f& gravity);
    [[nodiscard]] sf::Vector2f getGravity() const;

  private:
    b2Body* createInternalBody(const b2BodyDef* b2_body_def);
    void destroyInternalBody(b2Body* b2_body);

    b2Joint* createInternalJoint(const b2JointDef* b2_joint_def);
    void destroyInternalJoint(b2Joint* b2_joint);

    void beforeSimulation();
    void afterSimulation();

  private:
    scene::SceneNode& m_scene_node;
    std::unique_ptr<b2World> m_b2_world;
  };

} // namespace egnim::physics

#endif //PHYSICS_WORLD_H
