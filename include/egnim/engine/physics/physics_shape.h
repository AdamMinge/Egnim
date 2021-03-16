#ifndef PHYSICS_SHAPE_H
#define PHYSICS_SHAPE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <list>
/* -------------------------------------------------------------------------- */

class b2Fixture;
class b2Shape;

namespace egnim::physics
{
  class PhysicsBody;

  class PhysicsMaterial
  {
  public:
    [[maybe_unused]] static const PhysicsMaterial DefaultMaterial;

  public:
    PhysicsMaterial(float density, float restitution, float friction) noexcept;

    void setDensity(float density);
    void setRestitution(float restitution);
    void setFriction(float friction);

    [[nodiscard]] float getDensity() const;
    [[nodiscard]] float getRestitution() const;
    [[nodiscard]] float getFriction() const;

  private:
    float m_density;
    float m_restitution;
    float m_friction;
  };

  class PhysicsShape
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
    PhysicsMaterial getPhysicsMaterial();

    void setDensity(float density);
    void setRestitution(float restitution);
    void setFriction(float friction);

    [[nodiscard]] float getDensity() const;
    [[nodiscard]] float getRestitution() const;
    [[nodiscard]] float getFriction() const;

    [[nodiscard]] Type getType() const;

    [[nodiscard]] PhysicsBody* getPhysicsBody();
    [[nodiscard]] const PhysicsBody* getPhysicsBody() const;

  protected:
    explicit PhysicsShape(Type type, const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);

    [[nodiscard]] b2Fixture* createInternalFixture();
    void destroyInternalFixture();
    void updateInternalFixture();

    [[nodiscard]] virtual b2Shape& createInternalShape() const = 0;

  private:
    void setPhysicsBody(PhysicsBody* physics_body);

  private:
    PhysicsBody* m_physics_body;
    b2Fixture* m_b2_fixture;
    Type m_type;
    PhysicsMaterial m_physics_material;
  };

  class PhysicsShapeCircle : public PhysicsShape
  {
  public:
    explicit PhysicsShapeCircle(float radius,
                                const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);
    ~PhysicsShapeCircle() override = default;

  protected:
    [[nodiscard]] b2Shape& createInternalShape() const override;

  private:
    float m_radius;
  };

  class PhysicsShapeBox : public PhysicsShape
  {
  public:
    explicit PhysicsShapeBox(const sf::Vector2f& size,
                             const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);
    ~PhysicsShapeBox() override = default;

  protected:
    [[nodiscard]] b2Shape& createInternalShape() const override;

  private:
    sf::Vector2f m_size;
  };

  class PhysicsShapePolygon : public PhysicsShape
  {
  public:
    explicit PhysicsShapePolygon(std::list<sf::Vector2f> points,
                                 const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);
    ~PhysicsShapePolygon() override = default;

  protected:
    [[nodiscard]] b2Shape& createInternalShape() const override;

  private:
    std::list<sf::Vector2f> m_points;
  };

  class PhysicsShapeEdgeSegment : public PhysicsShape
  {
  public:
    explicit PhysicsShapeEdgeSegment(const sf::Vector2f& first, const sf::Vector2f& second,
                                     const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);
    ~PhysicsShapeEdgeSegment() override = default;

  protected:
    [[nodiscard]] b2Shape& createInternalShape() const override;

  private:
    sf::Vector2f m_first;
    sf::Vector2f m_second;
  };

  class PhysicsShapeEdgeBox : public PhysicsShape
  {
    explicit PhysicsShapeEdgeBox(const sf::Vector2f& size,
                                 const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);
    ~PhysicsShapeEdgeBox() override = default;

  protected:
    [[nodiscard]] b2Shape& createInternalShape() const override;

  private:
    sf::Vector2f m_size;
  };

  class PhysicsShapeEdgePolygon : public PhysicsShape
  {
    explicit PhysicsShapeEdgePolygon(std::list<sf::Vector2f> points,
                                     const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);
    ~PhysicsShapeEdgePolygon() override = default;

  protected:
    [[nodiscard]] b2Shape& createInternalShape() const override;

  private:
    std::list<sf::Vector2f> m_points;
  };

  class PhysicsShapeEdgeChain : public PhysicsShape
  {
    explicit PhysicsShapeEdgeChain(std::list<sf::Vector2f> points,
                                   const PhysicsMaterial& physics_material = PhysicsMaterial::DefaultMaterial);
    ~PhysicsShapeEdgeChain() override = default;

  protected:
    [[nodiscard]] b2Shape& createInternalShape() const override;

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
