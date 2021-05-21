#ifndef PHYSICS_HELPER_H
#define PHYSICS_HELPER_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Color.hpp>
/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_math.h>
#include <box2d/b2_shape.h>
#include <box2d/b2_draw.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_contact_impulse.h>
#include <egnim/engine/physics/physics_contact.h>
#include <egnim/engine/physics/physics_manifold.h>
#include <egnim/engine/physics/physics_manifold_point.h>
#include <egnim/engine/physics/physics_mass_info.h>
/* -------------------------------------------------------------------------- */

class b2Contact;
class b2Manifold;
class b2ManifoldPoint;
class b2ContactImpulse;

namespace egnim::physics::priv
{

  class PhysicsHelper
  {
  public:
    static PhysicsContact cast(const b2Contact& b2_contact);
    static PhysicsManifold cast(const b2Manifold& b2_manifold);
    static PhysicsManifoldPoint cast(const b2ManifoldPoint& b2_manifold_point);
    static PhysicsContactImpulse cast(const b2ContactImpulse& b2_contact_impulse);

    static sf::Vector2f cast(const b2Vec2& point);
    static b2Vec2 cast(const sf::Vector2f& point);
    static PhysicsMassInfo cast(const b2MassData& b2_mass_data);
    static b2MassData cast(const PhysicsMassInfo& mass_info);
    static sf::Color cast(const b2Color& color);
    static b2Color cast(const sf::Color& color);

    static b2Vec2 pixel_to_meter(const sf::Vector2f& pixel_point);
    static sf::Vector2f meter_to_pixel(const b2Vec2& meter_point);

    static float pixel_to_meter(float pixel);
    static float meter_to_pixel(float meter);

    static float angleToRadian(float angle);
    static float radianToAngle(float radian);

  private:
    static float s_meter_to_pixel;

  private:
    explicit PhysicsHelper() = default;
    ~PhysicsHelper() = default;
  };

} // namespace egnim::physics::priv

#endif //PHYSICS_HELPER_H
