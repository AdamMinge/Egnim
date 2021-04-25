#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <list>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

class b2World;

class b2Body;
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
  class PhysicsWorldCallback;

  class EGNIM_UTILITY_API PhysicsWorld
  {
    friend PhysicsBody;
    friend PhysicsJoint;
    friend PhysicsWorldCallback;

  public:
    explicit PhysicsWorld(scene::SceneNode& scene_node, const sf::Vector2f& gravity);
    ~PhysicsWorld();

    void update(float time_step, int32_t velocity_iterations, int32_t position_iterations);

    void setGravity(const sf::Vector2f& gravity);
    [[nodiscard]] sf::Vector2f getGravity() const;

    [[nodiscard]] const std::list<PhysicsBody*>& getPhysicsBodies() const;
    [[nodiscard]] const std::list<PhysicsJoint*>& getPhysicsJoints() const;

  private:
    void attachPhysicsBody(PhysicsBody* physics_body);
    void detachPhysicsBody(PhysicsBody* physics_body);

    void attachPhysicsJoint(PhysicsJoint* physics_joint);
    void detachPhysicsJoint(PhysicsJoint* physics_joint);

    b2Body* createInternalBody(const b2BodyDef* b2_body_def);
    void destroyInternalBody(b2Body* b2_body);

    b2Joint* createInternalJoint(const b2JointDef* b2_joint_def);
    void destroyInternalJoint(b2Joint* b2_joint);

    void beforeSimulation();
    void afterSimulation();

  private:
    scene::SceneNode& m_scene_node;
    std::unique_ptr<PhysicsWorldCallback> m_physics_world_callback;
    std::unique_ptr<b2World> m_b2_world;
    std::list<PhysicsBody*> m_physics_bodies;
    std::list<PhysicsJoint*> m_physics_joints;
  };

} // namespace egnim::physics

#endif //PHYSICS_WORLD_H
