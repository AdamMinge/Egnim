#ifndef PHYSICS_JOINT_H
#define PHYSICS_JOINT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <cassert>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/scene/node.h>
/* -------------------------------------------------------------------------- */

class b2Joint;
class b2Body;
struct b2JointDef;

namespace egnim::physics
{

  class PhysicsBody;
  class PhysicsWorld;

  class EGNIM_UTILITY_API PhysicsJoint : public scene::Node
  {
    EGNIM_CLASS(PhysicsJoint, Node)

    friend PhysicsWorld;

  public:
    enum class Type;

  public:
    ~PhysicsJoint() override;

    [[nodiscard]] const PhysicsBody& getFirstPhysicsBody() const;
    [[nodiscard]] PhysicsBody& getFirstPhysicsBody();

    [[nodiscard]] const PhysicsBody& getSecondPhysicsBody() const;
    [[nodiscard]] PhysicsBody& getSecondPhysicsBody();

    [[nodiscard]] virtual sf::Vector2f getFirstAnchor() const = 0;
    [[nodiscard]] virtual sf::Vector2f getSecondAnchor() const = 0;

    [[nodiscard]] virtual sf::Vector2f getReactionForce(float inv_dt) const = 0;
    [[nodiscard]] virtual float getReactionTorque(float inv_dt) const = 0;

    [[nodiscard]] Type getType() const;

    void accept(scene::SceneVisitor& visitor) override;

  protected:
    explicit PhysicsJoint(Type type, PhysicsBody& first_physics_body, PhysicsBody& second_physics_body);

    void onEnter() override;
    void onExit() override;

    void createInternalJoint();
    void destroyInternalJoint();

    [[nodiscard]] virtual std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const = 0;

    template<typename TYPE = PhysicsJoint> [[nodiscard]] const TYPE* getInternalJoint() const;
    template<typename TYPE = PhysicsJoint> [[nodiscard]] TYPE* getInternalJoint();

  private:
    Type m_type;
    PhysicsWorld* m_physics_world;
    PhysicsBody& m_first_physics_body;
    PhysicsBody& m_second_physics_body;
    b2Joint* m_b2_joint;
  };

  class DistancePhysicsJoint : public PhysicsJoint
  {
  public:
    [[nodiscard]] static std::unique_ptr<DistancePhysicsJoint> create(
      PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
      const sf::Vector2f& first_anchor, const sf::Vector2f& second_anchor);

  public:
    ~DistancePhysicsJoint() override;

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

    [[nodiscard]] sf::Vector2f getLocalFirstAnchor() const;
    [[nodiscard]] sf::Vector2f getLocalSecondAnchor() const;

    [[nodiscard]] sf::Vector2f getFirstAnchor() const override;
    [[nodiscard]] sf::Vector2f getSecondAnchor() const override;

    [[nodiscard]] sf::Vector2f getReactionForce(float inv_dt) const override;
    [[nodiscard]] float getReactionTorque(float inv_dt) const override;

  protected:
    explicit DistancePhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                  const sf::Vector2f& first_anchor, const sf::Vector2f& second_anchor);

    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    sf::Vector2f m_first_local_anchor;
    sf::Vector2f m_second_local_anchor;
    float m_length;
    float m_min_length;
    float m_max_length;
    float m_stiffness;
    float m_damping;
  };

  class FrictionPhysicsJoint : public PhysicsJoint
  {
  public:
    [[nodiscard]] static std::unique_ptr<FrictionPhysicsJoint> create(
      PhysicsBody& first_physics_body, PhysicsBody& second_physics_body, const sf::Vector2f& anchor);

  public:
    ~FrictionPhysicsJoint() override;

    void setMaxForce(float force);
    [[nodiscard]] float getMaxForce() const;

    void setMaxTorque(float torque);
    [[nodiscard]] float getMaxTorque() const;

    [[nodiscard]] sf::Vector2f getLocalFirstAnchor() const;
    [[nodiscard]] sf::Vector2f getLocalSecondAnchor() const;

    [[nodiscard]] sf::Vector2f getFirstAnchor() const override;
    [[nodiscard]] sf::Vector2f getSecondAnchor() const override;

    [[nodiscard]] sf::Vector2f getReactionForce(float inv_dt) const override;
    [[nodiscard]] float getReactionTorque(float inv_dt) const override;

  protected:
    explicit FrictionPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                  const sf::Vector2f& anchor);

    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    sf::Vector2f m_first_local_anchor;
    sf::Vector2f m_second_local_anchor;
    float m_max_force;
    float m_max_torque;
  };

  class MotorPhysicsJoint : public PhysicsJoint
  {
  public:
    [[nodiscard]] static std::unique_ptr<MotorPhysicsJoint> create(
      PhysicsBody& first_physics_body, PhysicsBody& second_physics_body);

  public:
    ~MotorPhysicsJoint() override;

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

    [[nodiscard]] sf::Vector2f getFirstAnchor() const override;
    [[nodiscard]] sf::Vector2f getSecondAnchor() const override;

    [[nodiscard]] sf::Vector2f getReactionForce(float inv_dt) const override;
    [[nodiscard]] float getReactionTorque(float inv_dt) const override;

  protected:
    explicit MotorPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body);

    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    float m_max_force;
    float m_max_torque;
    float m_correction_factory;
    sf::Vector2f m_linear_offset;
    float m_angular_offset;
  };

  class PrismaticPhysicsJoint : public PhysicsJoint
  {
  public:
    [[nodiscard]] static std::unique_ptr<PrismaticPhysicsJoint> create(
      PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
      const sf::Vector2f& anchor, const sf::Vector2f& axis);

  public:
    ~PrismaticPhysicsJoint() override;

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

    [[nodiscard]] sf::Vector2f getFirstAnchor() const override;
    [[nodiscard]] sf::Vector2f getSecondAnchor() const override;

    [[nodiscard]] sf::Vector2f getReactionForce(float inv_dt) const override;
    [[nodiscard]] float getReactionTorque(float inv_dt) const override;

  protected:
    explicit PrismaticPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                   const sf::Vector2f& anchor, const sf::Vector2f& axis);

    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    sf::Vector2f m_first_local_anchor;
    sf::Vector2f m_second_local_anchor;
    sf::Vector2f m_first_local_axis;
    bool m_enable_limit;
    bool m_enable_motor;
    float m_motor_speed;
    float m_max_motor_force;
    float m_reference_angle;
    float m_lower_translation;
    float m_upper_translation;
  };

  class PulleyPhysicsJoint : public PhysicsJoint
  {
  public:
    [[nodiscard]] static std::unique_ptr<PulleyPhysicsJoint> create(
      PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
      const sf::Vector2f& first_ground_anchor, const sf::Vector2f& second_ground_anchor,
      const sf::Vector2f& first_anchor, const sf::Vector2f& second_anchor, float ratio);

    ~PulleyPhysicsJoint() override;

    [[nodiscard]] float getFirstLength() const;
    [[nodiscard]] float getSecondLength() const;

    [[nodiscard]] float getRation() const;

    [[nodiscard]] float getCurrentFirstLength() const;
    [[nodiscard]] float getCurrentSecondLength() const;

    [[nodiscard]] sf::Vector2f getFirstGroundAnchor() const;
    [[nodiscard]] sf::Vector2f getSecondGroundAnchor() const;

    [[nodiscard]] sf::Vector2f getFirstAnchor() const override;
    [[nodiscard]] sf::Vector2f getSecondAnchor() const override;

    [[nodiscard]] sf::Vector2f getReactionForce(float inv_dt) const override;
    [[nodiscard]] float getReactionTorque(float inv_dt) const override;

  protected:
    explicit PulleyPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                const sf::Vector2f& first_ground_anchor, const sf::Vector2f& second_ground_anchor,
                                const sf::Vector2f& first_anchor, const sf::Vector2f& second_anchor, float ratio);

    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    sf::Vector2f m_first_ground_anchor;
    sf::Vector2f m_second_ground_anchor;
    sf::Vector2f m_first_local_anchor;
    sf::Vector2f m_second_local_anchor;
    float m_first_length;
    float m_second_length;
    float m_ratio;
  };

  class RevolutePhysicsJoint : public PhysicsJoint
  {
  public:
    [[nodiscard]] static std::unique_ptr<RevolutePhysicsJoint> create(
      PhysicsBody& first_physics_body, PhysicsBody& second_physics_body, const sf::Vector2f& anchor);

    ~RevolutePhysicsJoint() override;

    [[nodiscard]] float getReferenceAngle() const;
    [[nodiscard]] float getJointAngle() const;
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

    void setMaxMotorTorque(float torque);
    [[nodiscard]] float getMaxMotorTorque() const;
    [[nodiscard]] float getMotorTorque(float inv_dt) const;

    [[nodiscard]] sf::Vector2f getFirstAnchor() const override;
    [[nodiscard]] sf::Vector2f getSecondAnchor() const override;

    [[nodiscard]] sf::Vector2f getReactionForce(float inv_dt) const override;
    [[nodiscard]] float getReactionTorque(float inv_dt) const override;

  protected:
    explicit RevolutePhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                                  const sf::Vector2f& anchor);

    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    sf::Vector2f m_first_local_anchor;
    sf::Vector2f m_second_local_anchor;
    bool m_enable_limit;
    bool m_enable_motor;
    float m_motor_speed;
    float m_max_motor_torque;
    float m_reference_angle;
    float m_lower_angle;
    float m_upper_angle;
  };

  class WeldPhysicsJoint : public PhysicsJoint
  {
  public:
    [[nodiscard]] static std::unique_ptr<WeldPhysicsJoint> create(
      PhysicsBody& first_physics_body, PhysicsBody& second_physics_body, const sf::Vector2f& anchor);

    ~WeldPhysicsJoint() override;

    [[nodiscard]] float getReferenceAngle() const;

    void setStiffness(float stiffness);
    [[nodiscard]] float getStiffness() const;

    [[nodiscard]] sf::Vector2f getFirstAnchor() const override;
    [[nodiscard]] sf::Vector2f getSecondAnchor() const override;

    [[nodiscard]] sf::Vector2f getReactionForce(float inv_dt) const override;
    [[nodiscard]] float getReactionTorque(float inv_dt) const override;

  protected:
    explicit WeldPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                              const sf::Vector2f& anchor);

    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    sf::Vector2f m_first_local_anchor;
    sf::Vector2f m_second_local_anchor;
    float m_reference_angle;
    float m_stiffness;
  };

  class WheelPhysicsJoint : public PhysicsJoint
  {
  public:
    [[nodiscard]] static std::unique_ptr<WheelPhysicsJoint> create(
      PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
      const sf::Vector2f& anchor, const sf::Vector2f& axis);

    ~WheelPhysicsJoint() override;

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

    [[nodiscard]] sf::Vector2f getFirstAnchor() const override;
    [[nodiscard]] sf::Vector2f getSecondAnchor() const override;

    [[nodiscard]] sf::Vector2f getReactionForce(float inv_dt) const override;
    [[nodiscard]] float getReactionTorque(float inv_dt) const override;

  protected:
    explicit WheelPhysicsJoint(PhysicsBody& first_physics_body, PhysicsBody& second_physics_body,
                               const sf::Vector2f& anchor, const sf::Vector2f& axis);

    std::unique_ptr<b2JointDef> createInternalJointDef(
      b2Body* b2_first_physics_body, b2Body* b2_second_physics_body) const override;

  private:
    sf::Vector2f m_first_local_anchor;
    sf::Vector2f m_second_local_anchor;
    sf::Vector2f m_first_local_axis;
    bool m_enable_limit;
    bool m_enable_motor;
    float m_lower_translation;
    float m_upper_translation;
    float m_motor_speed;
    float m_max_motor_torque;
    float m_stiffness;
    float m_damping;
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
    auto joint = dynamic_cast<const TYPE*>(m_b2_joint);
    return joint;
  }

  template<typename TYPE>
  TYPE* PhysicsJoint::getInternalJoint()
  {
    auto joint = dynamic_cast<TYPE*>(m_b2_joint);
    return joint;
  }

} // namespace egnim::physics

#endif //PHYSICS_JOINT_H
