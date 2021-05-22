#ifndef PHYSICS_SHAPE_H
#define PHYSICS_SHAPE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <list>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/physics/physics_material.h>
#include <egnim/engine/physics/physics_mass_info.h>
#include <egnim/engine/scene/component.h>
/* -------------------------------------------------------------------------- */

class b2Fixture;
class b2Shape;

namespace egnim::physics
{
  class PhysicsBody;

  class EGNIM_UTILITY_API PhysicsShape : public scene::Component
  {
    friend PhysicsBody;

  public:
    enum class Type;

  public:
    ~PhysicsShape() override;

    PhysicsShape(const PhysicsShape&) = delete;
    PhysicsShape(PhysicsShape&&) = delete;

    PhysicsShape& operator=(const PhysicsShape&) = delete;
    PhysicsShape& operator=(PhysicsShape&&) = delete;

    void setPhysicsMaterial(const PhysicsMaterial& physics_material);
    [[nodiscard]] PhysicsMaterial getPhysicsMaterial() const;

    void setDensity(float density);
    void setRestitution(float restitution);
    void setFriction(float friction);
    void setRestitutionThreshold(float threshold);

    [[nodiscard]] float getDensity() const;
    [[nodiscard]] float getRestitution() const;
    [[nodiscard]] float getFriction() const;
    [[nodiscard]] float getRestitutionThreshold() const;

    void setContactTestBitmask(std::uint16_t bitmask);
    [[nodiscard]] std::uint16_t getContactTestBitmask() const;

    void setCollisionBitmask(std::uint16_t bitmask);
    [[nodiscard]] std::uint16_t getCollisionBitmask() const;

    void setGroup(std::int16_t group);
    [[nodiscard]] std::int16_t getGroup() const;

    void setSensor(bool sensor);
    [[nodiscard]] bool isSensor() const;

    [[nodiscard]] virtual int32_t getChildCount() const = 0;

    [[nodiscard]] Type getType() const;

    [[nodiscard]] PhysicsBody* getPhysicsBody();
    [[nodiscard]] const PhysicsBody* getPhysicsBody() const;

    [[nodiscard]] virtual PhysicsMassInfo getMassInfo() const = 0;

  protected:
    explicit PhysicsShape(Type type, const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

    void onEnter() override;
    void onExit() override;

    void createInternalFixture();
    void destroyInternalFixture();
    void updateInternalFixture();

    [[nodiscard]] virtual std::unique_ptr<b2Shape> createInternalShape() const = 0;

  private:
    PhysicsBody* m_physics_body;
    b2Fixture* m_b2_fixture;
    Type m_type;
    PhysicsMaterial m_physics_material;
    std::uint16_t m_contact_test_bitmask;
    std::uint16_t m_collision_bitmask;
    std::int16_t m_group_index;
    bool m_sensor;
  };

  class PhysicsShapeCircle : public PhysicsShape
  {
  public:
    [[nodiscard]] static std::unique_ptr<PhysicsShapeCircle> create(
      float radius, const sf::Vector2f& offset, const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

  public:
    ~PhysicsShapeCircle() override;

    [[nodiscard]] float getRadius() const;
    [[nodiscard]] const sf::Vector2f& getOffset() const;

    [[nodiscard]] int32_t getChildCount() const override;

    [[nodiscard]] PhysicsMassInfo getMassInfo() const override;

  protected:
    explicit PhysicsShapeCircle(float radius, const sf::Vector2f& offset,
                                const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

    [[nodiscard]] std::unique_ptr<b2Shape> createInternalShape() const override;

  private:
    float m_radius;
    sf::Vector2f m_offset;
  };

  class PhysicsShapeBox : public PhysicsShape
  {
  public:
    [[nodiscard]] static std::unique_ptr<PhysicsShapeBox> create(
      const sf::Vector2f& size, const sf::Vector2f& offset, const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

  public:
    ~PhysicsShapeBox() override;

    [[nodiscard]] const sf::Vector2f& getSize() const;
    [[nodiscard]] const sf::Vector2f& getOffset() const;

    [[nodiscard]] int32_t getChildCount() const override;

    [[nodiscard]] PhysicsMassInfo getMassInfo() const override;

  protected:
    explicit PhysicsShapeBox(const sf::Vector2f& size, const sf::Vector2f& offset,
                             const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

    [[nodiscard]] std::unique_ptr<b2Shape> createInternalShape() const override;

  private:
    sf::Vector2f m_size;
    sf::Vector2f m_offset;
  };

  class PhysicsShapePolygon : public PhysicsShape
  {
  public:
    [[nodiscard]] static std::unique_ptr<PhysicsShapePolygon> create(
      std::list<sf::Vector2f> points, const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

  public:
    ~PhysicsShapePolygon() override;

    [[nodiscard]] const std::list<sf::Vector2f>& getPoints() const;

    [[nodiscard]] int32_t getChildCount() const override;

    [[nodiscard]] PhysicsMassInfo getMassInfo() const override;

  protected:
    explicit PhysicsShapePolygon(std::list<sf::Vector2f> points,
                                 const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

    [[nodiscard]] std::unique_ptr<b2Shape> createInternalShape() const override;

  private:
    std::list<sf::Vector2f> m_points;
  };

  class PhysicsShapeEdgeSegment : public PhysicsShape
  {
  public:
    [[nodiscard]] static std::unique_ptr<PhysicsShapeEdgeSegment> create(
      const sf::Vector2f& first, const sf::Vector2f& second, const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

  public:
    ~PhysicsShapeEdgeSegment() override;

    [[nodiscard]] const sf::Vector2f& getFirstPosition() const;
    [[nodiscard]] const sf::Vector2f& getSecondPosition() const;

    [[nodiscard]] int32_t getChildCount() const override;

    [[nodiscard]] PhysicsMassInfo getMassInfo() const override;

  protected:
    explicit PhysicsShapeEdgeSegment(const sf::Vector2f& first, const sf::Vector2f& second,
                                     const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

    [[nodiscard]] std::unique_ptr<b2Shape> createInternalShape() const override;

  private:
    sf::Vector2f m_first;
    sf::Vector2f m_second;
  };

  class PhysicsShapeEdgeBox : public PhysicsShape
  {
  public:
    [[nodiscard]] static std::unique_ptr<PhysicsShapeEdgeBox> create(
      const sf::Vector2f& size, const sf::Vector2f& offset, const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

  public:
    ~PhysicsShapeEdgeBox() override;

    [[nodiscard]] const sf::Vector2f& getSize() const;
    [[nodiscard]] const sf::Vector2f& getOffset() const;

    [[nodiscard]] int32_t getChildCount() const override;

    [[nodiscard]] PhysicsMassInfo getMassInfo() const override;

  protected:
    explicit PhysicsShapeEdgeBox(const sf::Vector2f& size, const sf::Vector2f& offset,
                                 const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

    [[nodiscard]] std::unique_ptr<b2Shape> createInternalShape() const override;

  private:
    sf::Vector2f m_size;
    sf::Vector2f m_offset;
  };

  class PhysicsShapeEdgePolygon : public PhysicsShape
  {
  public:
    [[nodiscard]] static std::unique_ptr<PhysicsShapeEdgePolygon> create(
      std::list<sf::Vector2f> points, const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

  public:
    ~PhysicsShapeEdgePolygon() override;

    [[nodiscard]] const std::list<sf::Vector2f>& getPoints() const;

    [[nodiscard]] int32_t getChildCount() const override;

    [[nodiscard]] PhysicsMassInfo getMassInfo() const override;

  protected:
    explicit PhysicsShapeEdgePolygon(std::list<sf::Vector2f> points,
                                     const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

    [[nodiscard]] std::unique_ptr<b2Shape> createInternalShape() const override;

  private:
    std::list<sf::Vector2f> m_points;
  };

  class PhysicsShapeEdgeChain : public PhysicsShape
  {
  public:
    [[nodiscard]] static std::unique_ptr<PhysicsShapeEdgeChain> create(
      std::list<sf::Vector2f> points, const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

  public:
    ~PhysicsShapeEdgeChain() override;

    [[nodiscard]] const std::list<sf::Vector2f>& getPoints() const;

    [[nodiscard]] int32_t getChildCount() const override;

    [[nodiscard]] PhysicsMassInfo getMassInfo() const override;

  protected:
    explicit PhysicsShapeEdgeChain(std::list<sf::Vector2f> points,
                                   const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

    [[nodiscard]] std::unique_ptr<b2Shape> createInternalShape() const override;

  private:
    std::list<sf::Vector2f> m_points;
  };

  enum class PhysicsShape::Type
  {
    Circle,
    Box,
    Polygon,
    EdgeSegment,
    EdgeBox,
    EdgePolygon,
    EdgeChain
  };

} // namespace egnim::physics

#endif //PHYSICS_SHAPE_H
