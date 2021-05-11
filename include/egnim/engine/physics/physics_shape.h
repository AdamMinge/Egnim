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
/* -------------------------------------------------------------------------- */

class b2Fixture;
class b2Shape;

namespace egnim::physics
{
  class PhysicsBody;

  class EGNIM_UTILITY_API PhysicsShape
  {
    friend PhysicsBody;

  public:
    enum class Type;

  public:
    virtual ~PhysicsShape();

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

    [[nodiscard]] virtual std::unique_ptr<PhysicsShape> clone() const = 0;

  protected:
    explicit PhysicsShape(Type type, const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

    void createInternalFixture();
    void destroyInternalFixture();
    void updateInternalFixture();

    [[nodiscard]] virtual std::unique_ptr<b2Shape> createInternalShape() const = 0;

    void initializeClone(PhysicsShape& physics_shape) const;

  private:
    void setPhysicsBody(PhysicsBody* physics_body);

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
    explicit PhysicsShapeCircle(float radius, const sf::Vector2f& offset,
                                const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);
    ~PhysicsShapeCircle() override = default;

    [[nodiscard]] float getRadius() const;
    [[nodiscard]] const sf::Vector2f& getOffset() const;

    [[nodiscard]] int32_t getChildCount() const override;

    [[nodiscard]] std::unique_ptr<PhysicsShape> clone() const override;

  protected:
    [[nodiscard]] std::unique_ptr<b2Shape> createInternalShape() const override;

  private:
    float m_radius;
    sf::Vector2f m_offset;
  };

  class PhysicsShapeBox : public PhysicsShape
  {
  public:
    explicit PhysicsShapeBox(const sf::Vector2f& size, const sf::Vector2f& offset,
                             const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);
    ~PhysicsShapeBox() override = default;

    [[nodiscard]] const sf::Vector2f& getSize() const;
    [[nodiscard]] const sf::Vector2f& getOffset() const;

    [[nodiscard]] int32_t getChildCount() const override;

    [[nodiscard]] std::unique_ptr<PhysicsShape> clone() const override;

  protected:
    [[nodiscard]] std::unique_ptr<b2Shape> createInternalShape() const override;

  private:
    sf::Vector2f m_size;
    sf::Vector2f m_offset;
  };

  class PhysicsShapePolygon : public PhysicsShape
  {
  public:
    explicit PhysicsShapePolygon(std::list<sf::Vector2f> points,
                                 const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);
    ~PhysicsShapePolygon() override = default;

    [[nodiscard]] const std::list<sf::Vector2f>& getPoints() const;

    [[nodiscard]] int32_t getChildCount() const override;

    [[nodiscard]] std::unique_ptr<PhysicsShape> clone() const override;

  protected:
    [[nodiscard]] std::unique_ptr<b2Shape> createInternalShape() const override;

  private:
    std::list<sf::Vector2f> m_points;
  };

  class PhysicsShapeEdgeSegment : public PhysicsShape
  {
  public:
    explicit PhysicsShapeEdgeSegment(const sf::Vector2f& first, const sf::Vector2f& second,
                                     const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);
    ~PhysicsShapeEdgeSegment() override = default;

    [[nodiscard]] const sf::Vector2f& getFirstPosition() const;
    [[nodiscard]] const sf::Vector2f& getSecondPosition() const;

    [[nodiscard]] int32_t getChildCount() const override;

    [[nodiscard]] std::unique_ptr<PhysicsShape> clone() const override;

  protected:
    [[nodiscard]] std::unique_ptr<b2Shape> createInternalShape() const override;

  private:
    sf::Vector2f m_first;
    sf::Vector2f m_second;
  };

  class PhysicsShapeEdgeBox : public PhysicsShape
  {
  public:
    explicit PhysicsShapeEdgeBox(const sf::Vector2f& size, const sf::Vector2f& offset,
                                 const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);
    ~PhysicsShapeEdgeBox() override = default;

    [[nodiscard]] const sf::Vector2f& getSize() const;
    [[nodiscard]] const sf::Vector2f& getOffset() const;

    [[nodiscard]] int32_t getChildCount() const override;

    [[nodiscard]] std::unique_ptr<PhysicsShape> clone() const override;

  protected:
    [[nodiscard]] std::unique_ptr<b2Shape> createInternalShape() const override;

  private:
    sf::Vector2f m_size;
    sf::Vector2f m_offset;
  };

  class PhysicsShapeEdgePolygon : public PhysicsShape
  {
  public:
    explicit PhysicsShapeEdgePolygon(std::list<sf::Vector2f> points,
                                     const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);
    ~PhysicsShapeEdgePolygon() override = default;

    [[nodiscard]] const std::list<sf::Vector2f>& getPoints() const;

    [[nodiscard]] int32_t getChildCount() const override;

    [[nodiscard]] std::unique_ptr<PhysicsShape> clone() const override;

  protected:
    [[nodiscard]] std::unique_ptr<b2Shape> createInternalShape() const override;

  private:
    std::list<sf::Vector2f> m_points;
  };

  class PhysicsShapeEdgeChain : public PhysicsShape
  {
  public:
    explicit PhysicsShapeEdgeChain(std::list<sf::Vector2f> points,
                                   const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);
    ~PhysicsShapeEdgeChain() override = default;

    [[nodiscard]] const std::list<sf::Vector2f>& getPoints() const;

    [[nodiscard]] int32_t getChildCount() const override;

    [[nodiscard]] std::unique_ptr<PhysicsShape> clone() const override;

  protected:
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
