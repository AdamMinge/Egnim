#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <vector>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/scene/component.h>
/* -------------------------------------------------------------------------- */

class b2Body;
class b2Fixture;
struct b2FixtureDef;

namespace egnim::physics
{

  class PhysicsWorld;
  class PhysicsShape;
  class PhysicsJoint;

  class PhysicsBody : public scene::Component
  {
    friend PhysicsWorld;
    friend PhysicsShape;
    friend PhysicsJoint;

  public:
    enum class Type;

  public:
    explicit PhysicsBody(PhysicsWorld& physics_world, Type type);
    ~PhysicsBody() override;

    PhysicsBody(const PhysicsBody&) = delete;
    PhysicsBody(PhysicsBody&&) = delete;

    PhysicsBody& operator=(const PhysicsBody&) = delete;
    PhysicsBody& operator=(PhysicsBody&&) = delete;

    void setPosition(const sf::Vector2f& position);
    [[nodiscard]] sf::Vector2f getPosition() const;

    void setRotation(float angle);
    [[nodiscard]] float getRotation() const;

    void update(sf::Time dt) override;

    [[nodiscard]] PhysicsWorld* getPhysicsWorld();
    [[nodiscard]] const PhysicsWorld* getPhysicsWorld() const;

    void setLinearVelocity(const sf::Vector2f& linear_velocity);
    [[nodiscard]] sf::Vector2f getLinearVelocity() const;

    void setAngularVelocity(float omega);
    [[nodiscard]] float getAngularVelocity() const;

    void applyForce(const sf::Vector2f& force, const sf::Vector2f& point);
    void applyForceToCenter(const sf::Vector2f& force);

    void applyTorque(float torque);
    void applyLinearImpulse(const sf::Vector2f& impulse, const sf::Vector2f& point);
    void applyLinearImpulseToCenter(const sf::Vector2f& impulse);
    void applyAngularImpulse(float impulse);

    [[nodiscard]] float getMass() const;
    [[nodiscard]] float getInertia() const;

    void setType(Type type);
    [[nodiscard]] Type getType() const;

    void setLinearDamping(float linear_damping);
    [[nodiscard]] float getLinearDamping() const;

    void setAngularDamping(float angular_damping);
    [[nodiscard]] float getAngularDamping() const;

    void setBullet(bool bullet = true);
    [[nodiscard]] bool isBullet() const;

    void setGravityScale(float gravity_scale);
    [[nodiscard]] float getGravityScale() const;

    void attachPhysicsShape(std::unique_ptr<PhysicsShape> physics_shape);
    std::unique_ptr<PhysicsShape> detachPhysicsShape(const PhysicsShape& physics_shape);
    [[nodiscard]] const std::vector<std::unique_ptr<PhysicsShape>>& getPhysicsShapes() const;

    [[nodiscard]] std::vector<PhysicsJoint*> getPhysicsJoints() const;

  private:
    void createInternalBody(Type type);
    void destroyInternalBody();

    void beforeSimulation();
    void afterSimulation();

    [[nodiscard]] b2Fixture* createInternalFixture(const b2FixtureDef* b2_fixture_def);
    void destroyInternalFixture(b2Fixture* b2_fixture);

    [[nodiscard]] const b2Body* getInternalBody() const;
    [[nodiscard]] b2Body* getInternalBody();

  private:
    PhysicsWorld& m_physics_world;
    b2Body* m_b2_body;
    std::vector<std::unique_ptr<PhysicsShape>> m_physics_shapes;
  };

  enum class PhysicsBody::Type
  {
    StaticBody = 0,
    KinematicBody = 1,
    DynamicBody = 2
  };

}

#endif //PHYSICS_BODY_H
