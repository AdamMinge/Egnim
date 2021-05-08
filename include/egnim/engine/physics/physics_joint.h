#ifndef PHYSICS_JOINT_H
#define PHYSICS_JOINT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <cassert>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

class b2Joint;
class b2Body;
struct b2JointDef;

namespace egnim::physics
{

  class PhysicsBody;
  class PhysicsWorld;

  class EGNIM_UTILITY_API PhysicsJoint
  {
    friend PhysicsWorld;

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

    [[nodiscard]] sf::Vector2f getFirstAnchor() const;
    [[nodiscard]] sf::Vector2f getSecondAnchor() const;

    [[nodiscard]] sf::Vector2f getReactionForce(float inv_dt) const;
    [[nodiscard]] float getReactionTorque(float inv_dt) const;

    [[nodiscard]] Type getType() const;

  protected:
    explicit PhysicsJoint(Type type, PhysicsBody& first_physics_body, PhysicsBody& second_physics_body);

    void createInternalJoint();
    void destroyInternalJoint();

    [[nodiscard]] virtual std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const = 0;

    template<typename TYPE = PhysicsJoint> [[nodiscard]] const TYPE* getInternalJoint() const;
    template<typename TYPE = PhysicsJoint> [[nodiscard]] TYPE* getInternalJoint();

  private:
    Type m_type;
    PhysicsWorld& m_physics_world;
    PhysicsBody& m_first_physics_body;
    PhysicsBody& m_second_physics_body;
    b2Joint* m_b2_joint;
  };

  class DistancePhysicsJoint : public PhysicsJoint
  {
  public:
    explicit DistancePhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                  const sf::Vector2f& first_anchor, const sf::Vector2f& second_anchor);

    void setLength(float length);
    [[nodiscard]] float getLength() const;

    void setMinLength(float min_length);
    [[nodiscard]] float getMinLength() const;

    void setMaxLength(float max_length);
    [[nodiscard]] float getMaxLength() const;

    [[nodiscard]] float getCurrentLength() const;

    void setStiffness(float stiffness);
    [[nodiscard]] float getStiffness() const;

    void setDamping(float damping);
    [[nodiscard]] float getDamping() const;

  protected:
    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    sf::Vector2f m_first_anchor;
    sf::Vector2f m_second_anchor;
  };

  class FrictionPhysicsJoint : public PhysicsJoint
  {
  public:
    explicit FrictionPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                  const sf::Vector2f& anchor);

    [[nodiscard]] const sf::Vector2f& getAnchor() const;

    void setMaxForce(float force);
    [[nodiscard]] float getMaxForce() const;

    void setMaxTorque(float torque);
    [[nodiscard]] float getMaxTorque() const;

  protected:
    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    sf::Vector2f m_anchor;
  };

  class MotorPhysicsJoint : public PhysicsJoint
  {
  public:
    explicit MotorPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body);

    void setMaxForce(float force);
    [[nodiscard]] float getMaxForce() const;

    void setMaxTorque(float torque);
    [[nodiscard]] float getMaxTorque() const;

    void setCorrectionFactory(float factory);
    [[nodiscard]] float getCorrectionFactory() const;

    void setLinearOffset(const sf::Vector2f& linear_offset);
    [[nodiscard]] sf::Vector2f getLinearOffset() const;

    void setAngularOffset(float angular_offset);
    [[nodiscard]] float getAngularOffset() const;

  protected:
    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;
  };

  class PrismaticPhysicsJoint : public PhysicsJoint
  {
  public:
    explicit PrismaticPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                   const sf::Vector2f& anchor, const sf::Vector2f& axis);

    [[nodiscard]] float getReferenceAngle() const;
    [[nodiscard]] float getJointTranslation() const;
    [[nodiscard]] float getJointSpeed() const;

    [[nodiscard]] bool isLimitEnabled() const;
    void enableLimit(bool enable);

    [[nodiscard]] float getLowerLimit() const;
    [[nodiscard]] float getUpperLimit() const;

    void setLimits(float lower, float upper);

    [[nodiscard]] bool isMotorEnabled() const;
    void enableMotor(bool enable);

    void setMotorSpeed(float speed);
    [[nodiscard]] float getMotorSpeed() const;

    void setMaxMotorForce(float force);
    [[nodiscard]] float getMaxMotorForce() const;
    [[nodiscard]] float getMotorForce(float inv_dt) const;

  protected:
    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    sf::Vector2f m_anchor;
    sf::Vector2f m_axis;
  };

  class PulleyPhysicsJoint : public PhysicsJoint
  {
  public:
    explicit PulleyPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                const sf::Vector2f& first_ground_anchor, const sf::Vector2f& second_ground_anchor,
                                const sf::Vector2f& first_anchor, const sf::Vector2f& second_anchor, float ration);

    [[nodiscard]] sf::Vector2f getFirstGroundAnchor() const;
    [[nodiscard]] sf::Vector2f getSecondGroundAnchor() const;

    [[nodiscard]] float getFirstLength() const;
    [[nodiscard]] float getSecondLength() const;

    [[nodiscard]] float getRation() const;

    [[nodiscard]] float getCurrentFirstLength() const;
    [[nodiscard]] float getCurrentSecondLength() const;

  protected:
    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    const sf::Vector2f& m_first_ground_anchor;
    const sf::Vector2f& m_second_ground_anchor;
    const sf::Vector2f& m_first_anchor;
    const sf::Vector2f& m_second_anchor;
    float m_ration;
  };

  class RevolutePhysicsJoint : public PhysicsJoint
  {
  public:
    explicit RevolutePhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                  const sf::Vector2f& anchor);

    [[nodiscard]] float getReferenceAngle() const;
    [[nodiscard]] float getJointAngle() const;
    [[nodiscard]] float getJointSpeed() const;

    [[nodiscard]] bool isLimitEnabled() const;
    void enableLimit(bool enable);

    [[nodiscard]] float getLowerLimit() const;
    [[nodiscard]] float getUppedLimit() const;
    void setLimits(float lower, float upper);

    [[nodiscard]] bool isMotorEnabled() const;
    void enableMotor(bool enable);

    void setMotorSpeed(float speed);
    [[nodiscard]] float getMotorSpeed() const;

    void setMaxMotorTorque(float torque);
    [[nodiscard]] float getMaxMotorTorque() const;

    [[nodiscard]] float getMotorTorque(float inv_dt) const;

  protected:
    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    sf::Vector2f m_anchor;
  };

  class WeldPhysicsJoint : public PhysicsJoint
  {
  public:
    explicit WeldPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                              const sf::Vector2f& anchor);

    [[nodiscard]] float getReferenceAngle() const;

    void setStiffness(float hz);
    [[nodiscard]] float getStiffness() const;

  protected:
    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    sf::Vector2f m_anchor;
  };

  class WheelPhysicsJoint : public PhysicsJoint
  {
  public:
    explicit WheelPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                               const sf::Vector2f& anchor, const sf::Vector2f& axis);

    [[nodiscard]] float getJointTranslation() const;
    [[nodiscard]] float getJointLinearSpeed() const;
    [[nodiscard]] float getJointAngle() const;
    [[nodiscard]] float getJointAngularSpeed() const;

    [[nodiscard]] bool isLimitEnabled() const;
    void enableLimit(bool enable);

    [[nodiscard]] float getLowerLimit() const;
    [[nodiscard]] float getUpperLimit() const;
    void setLimits(float lower, float upper);

    [[nodiscard]] bool isMotorEnabled() const;
    void enableMotor(bool enable);

    void setMotorSpeed(float speed);
    [[nodiscard]] float getMotorSpeed() const;

    void setMaxMotorTorque(float torque);
    [[nodiscard]] float getMaxMotorTorque() const;
    [[nodiscard]] float getMotorTorque(float inv_dt);

    void setStiffness(float stiffness);
    [[nodiscard]] float getStiffness() const;

    void setDamping(float damping);
    [[nodiscard]] float getDamping() const;

  protected:
    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    sf::Vector2f m_anchor;
    sf::Vector2f m_axis;
  };

  enum class PhysicsJoint::Type
  {
    Distance,
    Friction,
    Motor,
    Prismatic,
    Pulley,
    Revolute,
    Weld,
    Wheel
  };

  template<typename TYPE>
  const TYPE* PhysicsJoint::getInternalJoint() const
  {
    assert(m_b2_joint);
    auto joint = dynamic_cast<const TYPE*>(m_b2_joint);
    assert(joint);
    return joint;
  }

  template<typename TYPE>
  TYPE* PhysicsJoint::getInternalJoint()
  {
    assert(m_b2_joint);
    auto joint = dynamic_cast<TYPE*>(m_b2_joint);
    assert(joint);
    return joint;
  }

} // namespace egnim::physics

#endif //PHYSICS_JOINT_H
