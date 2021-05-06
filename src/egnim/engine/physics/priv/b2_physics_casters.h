#ifndef B2_PHYSICS_CASTERS_H
#define B2_PHYSICS_CASTERS_H

/* ----------------------------------- Local -------------------------------- */
#include <box2d/b2_math.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_contact_impulse.h>
#include <egnim/engine/physics/physics_contact.h>
#include <egnim/engine/physics/physics_manifold.h>
#include <egnim/engine/physics/physics_manifold_point.h>
/* -------------------------------------------------------------------------- */

class b2Contact;
class b2Manifold;
class b2ManifoldPoint;
class b2ContactImpulse;

namespace egnim::physics::priv
{

  PhysicsContact b2_cast(const b2Contact& b2_contact);
  PhysicsManifold b2_cast(const b2Manifold& b2_manifold);
  PhysicsManifoldPoint b2_cast(const b2ManifoldPoint& b2_manifold_point);
  PhysicsContactImpulse b2_cast(const b2ContactImpulse& b2_contact_impulse);

  b2Vec2 b2_cast(const sf::Vector2f& point);
  sf::Vector2f b2_cast(const b2Vec2& point);

  b2Vec2 b2_pixel_to_meter(const sf::Vector2f& pixel_point);
  sf::Vector2f b2_meter_to_pixel(const b2Vec2& meter_point);

  float b2_pixel_to_meter(float pixel);
  float b2_meter_to_pixel(float meter);

} // namespace egnim::physics::priv

#endif //B2_PHYSICS_CASTERS_H
