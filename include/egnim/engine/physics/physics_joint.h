#ifndef PHYSICS_JOINT_H
#define PHYSICS_JOINT_H

namespace egnim::physics
{

  class PhysicsBody;
  class PhysicsWorld;

  class PhysicsJoint
  {
  public:
    enum class Type;

  public:
    virtual ~PhysicsJoint();

    [[nodiscard]] const PhysicsBody* getFirstPhysicsBody() const;
    [[nodiscard]] PhysicsBody* getFirstPhysicsBody();

    [[nodiscard]] const PhysicsBody* getSecondPhysicsBody() const;
    [[nodiscard]] PhysicsBody* getSecondPhysicsBody();

    [[nodiscard]] const PhysicsWorld* getPhysicsWorld() const;
    [[nodiscard]] PhysicsWorld* getPhysicsWorld();

    [[nodiscard]] Type getType() const;

  protected:
    explicit PhysicsJoint(Type type, PhysicsBody& first_physics_body, PhysicsBody& second_physics_body);

  private:
    Type m_type;
    PhysicsWorld& m_physics_world;
    PhysicsBody& m_first_physics_body;
    PhysicsBody& m_second_physics_body;
  };

  enum class PhysicsJoint::Type
  {
    Distance,
    Friction,
    Gear,
    Motor,
    Mouse,
    Prismatic,
    Pulley,
    Revolute,
    Weld,
    Wheel
  };

} // namespace egnim::physics

#endif //PHYSICS_JOINT_H
