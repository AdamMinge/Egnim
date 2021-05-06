/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_world_callbacks.h>
#include <box2d/b2_collision.h>
#include <box2d/b2_contact.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/priv/b2_physics_casters.h>
#include <egnim/engine/physics/physics_shape.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics::priv {

PhysicsContact b2_cast(const b2Contact& b2_contact)
{
  auto& b2_contact_without_const = const_cast<b2Contact&>(b2_contact);

  auto first_shape = reinterpret_cast<PhysicsShape*>(b2_contact_without_const.GetFixtureA()->GetUserData().pointer);
  auto second_shape = reinterpret_cast<PhysicsShape*>(b2_contact_without_const.GetFixtureB()->GetUserData().pointer);
  auto physics_manifold = b2_cast(*b2_contact_without_const.GetManifold());

  auto physics_contact = PhysicsContact(first_shape, b2_contact.GetChildIndexA(),
                                        second_shape, b2_contact.GetChildIndexB(), physics_manifold);

  physics_contact.setTouching(b2_contact.IsTouching());
  physics_contact.setEnabled(b2_contact.IsEnabled());
  physics_contact.setFriction(b2_contact.GetFriction());
  physics_contact.setRestitution(b2_contact.GetRestitution());
  physics_contact.setRestitutionThreshold(b2_contact.GetRestitutionThreshold());
  physics_contact.setTangentSpeed(b2_contact.GetTangentSpeed());

  return physics_contact;
}

PhysicsManifold b2_cast(const b2Manifold& b2_manifold)
{
  std::list<PhysicsManifoldPoint> points;
  for(auto i = 0; i < b2_manifold.pointCount; ++i)
    points.push_back(b2_cast(b2_manifold.points[i]));

  return PhysicsManifold(static_cast<PhysicsManifold::Type>(b2_manifold.type),
                         priv::b2_meter_to_pixel(b2_manifold.localPoint),
                         sf::Vector2f(b2_manifold.localNormal.x, b2_manifold.localNormal.y),
                         points);
}

PhysicsManifoldPoint b2_cast(const b2ManifoldPoint& b2_manifold_point)
{
  return PhysicsManifoldPoint(priv::b2_meter_to_pixel(b2_manifold_point.localPoint),
                              b2_manifold_point.normalImpulse, b2_manifold_point.tangentImpulse);
}

PhysicsContactImpulse b2_cast(const b2ContactImpulse& b2_contact_impulse)
{
  std::list<float> normal_impulses;
  std::list<float> tangent_impulses;
  for(auto i = 0; i < b2_contact_impulse.count; ++i)
  {
    normal_impulses.push_back(b2_contact_impulse.normalImpulses[i]);
    tangent_impulses.push_back(b2_contact_impulse.tangentImpulses[i]);
  }

  return PhysicsContactImpulse(normal_impulses, tangent_impulses);
}

b2Vec2 b2_pixel_to_meter(const sf::Vector2f& pixel_point)
{
  return b2Vec2(b2_pixel_to_meter(pixel_point.x),
                b2_pixel_to_meter(pixel_point.y));
}

sf::Vector2f b2_meter_to_pixel(const b2Vec2& meter_point)
{
  return sf::Vector2f(b2_meter_to_pixel(meter_point.x),
                      b2_meter_to_pixel(meter_point.y));
}

float b2_pixel_to_meter(float pixel)
{
  return pixel * 30.f;
}

float b2_meter_to_pixel(float meter)
{
  return meter / 30.f;
}

} // namespace egnim::physics::priv