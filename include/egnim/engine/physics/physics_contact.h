#ifndef PHYSICS_CONTACT_H
#define PHYSICS_CONTACT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <list>
#include <memory>
/* -------------------------------------------------------------------------- */

class b2Manifold;
class b2Contact;

namespace egnim::physics
{

  class PhysicsShape;

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
    ~PhysicsManifold();

    void setLocalPoint(const sf::Vector2f& local_point);
    [[nodiscard]] sf::Vector2f getLocalPoint() const;

    void setLocalNormal(const sf::Vector2f& local_normal);
    [[nodiscard]] sf::Vector2f getLocalNormal() const;

    void setPoints(const std::list<PhysicsManifoldPoint>& points);
    [[nodiscard]] std::list<PhysicsManifoldPoint> getPoints() const;

    void setType(Type type);
    [[nodiscard]] Type getType() const;

  private:
    explicit PhysicsManifold(b2Manifold* manifold);

  private:
    b2Manifold* m_manifold;
  };

  class PhysicsContact
  {
  public:
    ~PhysicsContact();

    [[nodiscard]] PhysicsShape* getFirstShape();
    [[nodiscard]] const PhysicsShape* getFirstShape() const;

    [[nodiscard]] PhysicsShape* getSecondShape();
    [[nodiscard]] const PhysicsShape* getSecondShape() const;

    [[nodiscard]] PhysicsManifold* getPhysicsManifold();
    [[nodiscard]] const PhysicsManifold* getPhysicsManifold() const;

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
    explicit PhysicsContact(b2Contact* b2_contact);

  private:
    b2Contact* m_b2_contact;
    PhysicsManifold m_physics_manifold;
  };

  enum class PhysicsManifold::Type
  {
    CIRCLES,
    FACE_A,
    FACE_B
  };

} // namespace egnim::physics

#endif //PHYSICS_CONTACT_H
