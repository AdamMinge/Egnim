/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_world_callbacks.h>
#include <box2d/b2_collision.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_math.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/priv/physics_helper.h>
#include <egnim/engine/physics/physics_shape.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics::priv {

float PhysicsHelper::s_meter_to_pixel = 30;

PhysicsContact PhysicsHelper::cast(const b2Contact& b2_contact)
{
  auto& b2_contact_without_const = const_cast<b2Contact&>(b2_contact);

  auto first_shape = reinterpret_cast<PhysicsShape*>(b2_contact_without_const.GetFixtureA()->GetUserData().pointer);
  auto second_shape = reinterpret_cast<PhysicsShape*>(b2_contact_without_const.GetFixtureB()->GetUserData().pointer);
  auto physics_manifold = cast(*b2_contact_without_const.GetManifold());

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

PhysicsManifold PhysicsHelper::cast(const b2Manifold& b2_manifold)
{
  std::list<PhysicsManifoldPoint> points;
  for(auto i = 0; i < b2_manifold.pointCount; ++i)
    points.push_back(cast(b2_manifold.points[i]));

  return PhysicsManifold(static_cast<PhysicsManifold::Type>(b2_manifold.type),
                         PhysicsHelper::meter_to_pixel(b2_manifold.localPoint),
                         PhysicsHelper::meter_to_pixel(b2_manifold.localNormal),
                         points);
}

PhysicsManifoldPoint PhysicsHelper::cast(const b2ManifoldPoint& b2_manifold_point)
{
  return PhysicsManifoldPoint(PhysicsHelper::meter_to_pixel(b2_manifold_point.localPoint),
                              b2_manifold_point.normalImpulse, b2_manifold_point.tangentImpulse);
}

PhysicsContactImpulse PhysicsHelper::cast(const b2ContactImpulse& b2_contact_impulse)
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

PhysicsMassInfo PhysicsHelper::cast(const b2MassData& b2_mass_data)
{
  PhysicsMassInfo mass_info;
  mass_info.setCenter(meter_to_pixel(b2_mass_data.center));
  mass_info.setRotationalInertia(b2_mass_data.I);
  mass_info.setMass(b2_mass_data.mass);

  return mass_info;
}

b2MassData PhysicsHelper::cast(const PhysicsMassInfo& mass_info)
{
  b2MassData mass_data;
  mass_data.center = pixel_to_meter(mass_info.getCenter());
  mass_data.I = mass_info.getRotationalInertia();
  mass_data.mass = mass_info.getMass();

  return mass_data;
}

sf::Vector2f PhysicsHelper::cast(const b2Vec2& point)
{
  return sf::Vector2f(point.x, point.y);
}

b2Vec2 PhysicsHelper::cast(const sf::Vector2f& point)
{
  return b2Vec2(point.x, point.y);
}

b2Vec2 PhysicsHelper::pixel_to_meter(const sf::Vector2f& pixel_point)
{
  return b2Vec2(pixel_to_meter(pixel_point.x),
                pixel_to_meter(pixel_point.y));
}

sf::Vector2f PhysicsHelper::meter_to_pixel(const b2Vec2& meter_point)
{
  return sf::Vector2f(meter_to_pixel(meter_point.x),
                      meter_to_pixel(meter_point.y));
}

float PhysicsHelper::pixel_to_meter(float pixel)
{
  return pixel / s_meter_to_pixel;
}

float PhysicsHelper::meter_to_pixel(float meter)
{
  return meter * s_meter_to_pixel;
}

float PhysicsHelper::angleToRadian(float angle)
{
  return angle * b2_pi / 180;
}

float PhysicsHelper::radianToAngle(float radian)
{
  return radian * 180 / b2_pi;
}

} // namespace egnim::physics::priv