#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <functional>
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

  class PhysicsAABB;
  class PhysicsBody;
  class PhysicsJoint;
  class PhysicsShape;

  namespace priv
  {
    class PhysicsWorldCallback;
    class PhysicsQueryAABBCallback;
    class PhysicsRayCastCallback;
  }

  class EGNIM_UTILITY_API PhysicsWorld
  {
    friend PhysicsBody;
    friend PhysicsJoint;
    friend priv::PhysicsWorldCallback;

  public:
    using QueryAABBCallback = std::function<bool(PhysicsShape*)>;
    using RayCastCallback = std::function<float(PhysicsShape*, const sf::Vector2f&, const sf::Vector2f&, float)>;

  public:
    explicit PhysicsWorld(scene::SceneNode& scene_node, const sf::Vector2f& gravity);
    ~PhysicsWorld();

    void update(float time_step, int32_t velocity_iterations, int32_t position_iterations);

    void setGravity(const sf::Vector2f& gravity);
    [[nodiscard]] sf::Vector2f getGravity() const;

    [[nodiscard]] const std::list<PhysicsBody*>& getPhysicsBodies() const;
    [[nodiscard]] const std::list<PhysicsJoint*>& getPhysicsJoints() const;

    void setAllowSleeping(bool flag);
    void setWarmStarting(bool flag);
    void setContinuousPhysics(bool flag);
    void setSubStepping(bool flag);

    [[nodiscard]] bool getAllowSleeping() const;
    [[nodiscard]] bool getWarmStarting() const;
    [[nodiscard]] bool getContinuousPhysics() const;
    [[nodiscard]] bool getSubStepping() const;

    void queryAABB(const QueryAABBCallback& callback, const PhysicsAABB& physics_aabb);
    void rayCast(const RayCastCallback& callback, const sf::Vector2f& first_point, const sf::Vector2f& second_point);

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
    std::unique_ptr<priv::PhysicsWorldCallback> m_physics_world_callback;
    std::unique_ptr<priv::PhysicsQueryAABBCallback> m_physics_query_aabb_callback;
    std::unique_ptr<priv::PhysicsRayCastCallback> m_physics_ray_cast_callback;
    std::unique_ptr<b2World> m_b2_world;
    std::list<PhysicsBody*> m_physics_bodies;
    std::list<PhysicsJoint*> m_physics_joints;
  };

} // namespace egnim::physics

#endif //PHYSICS_WORLD_H
