#ifndef PHYSICS_CONTACT_H
#define PHYSICS_CONTACT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <list>
#include <memory>
/* -------------------------------------------------------------------------- */

namespace egnim::physics
{

  class PhysicsShape;

  class PhysicsContactImpulse
  {
  public:
    explicit PhysicsContactImpulse(std::list<float> normal_impulses, std::list<float> tangent_impulses);
    ~PhysicsContactImpulse();

    void setNormalImpulses(std::list<float> normal_impulses);
    [[nodiscard]] const std::list<float>& getNormalImpulses() const;

    void setTangentImpulses(std::list<float> tangent_impulses);
    [[nodiscard]] const std::list<float>& getTangentImpulses() const;

  private:
    std::list<float> m_normal_impulses;
    std::list<float> m_tangent_impulses;
  };

  class PhysicsManifoldPoint
  {
  public:
    explicit PhysicsManifoldPoint(sf::Vector2f local_point, float normal_impulse, float tangent_impulse);
    ~PhysicsManifoldPoint();

    void setLocalPoint(const sf::Vector2f& local_point);
    [[nodiscard]] const sf::Vector2f& getLocalPoint() const;

    void setNormalImpulse(float impulse);
    [[nodiscard]] float getNormalImpulse() const;

    void setTangentImpulse(float impulse);
    [[nodiscard]] float getTangentImpulse() const;

  private:
    sf::Vector2f m_local_point;
    float m_normal_impulse;
    float m_tangent_impulse;
  };

  class PhysicsManifold
  {
    friend class PhysicsContact;

  public:
    enum class Type;

  public:
    explicit PhysicsManifold(Type type, const sf::Vector2f& local_point, const sf::Vector2f& local_normal,
                             std::list<PhysicsManifoldPoint> points = {});
    ~PhysicsManifold();

    void setLocalPoint(const sf::Vector2f& local_point);
    [[nodiscard]] sf::Vector2f getLocalPoint() const;

    void setLocalNormal(const sf::Vector2f& local_normal);
    [[nodiscard]] sf::Vector2f getLocalNormal() const;

    void setPoints(const std::list<PhysicsManifoldPoint>& points);
    [[nodiscard]] const std::list<PhysicsManifoldPoint>& getPoints() const;

    void setType(Type type);
    [[nodiscard]] Type getType() const;

  private:
    Type m_type;
    sf::Vector2f m_local_point;
    sf::Vector2f m_local_normal;
    std::list<PhysicsManifoldPoint> m_points;
  };

  class PhysicsContact
  {
  public:
    explicit PhysicsContact(PhysicsShape* first_shape, PhysicsShape* second_shape, const PhysicsManifold& physics_manifold);
    ~PhysicsContact();

    [[nodiscard]] PhysicsShape* getFirstShape();
    [[nodiscard]] const PhysicsShape* getFirstShape() const;

    [[nodiscard]] PhysicsShape* getSecondShape();
    [[nodiscard]] const PhysicsShape* getSecondShape() const;

    [[nodiscard]] PhysicsManifold* getPhysicsManifold();
    [[nodiscard]] const PhysicsManifold* getPhysicsManifold() const;

    void setTouching(bool touching);
    [[nodiscard]] bool isTouching() const;

    void setEnabled(bool enable);
    [[nodiscard]] bool isEnabled() const;

    void setFriction(float friction);
    [[nodiscard]] float getFriction() const;
    void resetFriction();

    void setRestitution(float restitution);
    [[nodiscard]] float getRestitution() const;
    void resetRestitution();

    void setRestitutionThreshold(float threshold);
    [[nodiscard]] float getRestitutionThreshold() const;
    void resetRestitutionThreshold();

    void setTangentSpeed(float speed);
    [[nodiscard]] float getTangentSpeed() const;

  private:
    PhysicsShape* m_first_shape;
    PhysicsShape* m_second_shape;
    PhysicsManifold m_physics_manifold;
    bool m_touching;
    bool m_enabled;
    float m_friction;
    float m_restitution;
    float m_threshold;
    float m_speed;
  };

  enum class PhysicsManifold::Type
  {
    CIRCLES,
    FACE_A,
    FACE_B
  };

} // namespace egnim::physics

#endif //PHYSICS_CONTACT_H
