/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_fixture.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/priv/physics_world_callbacks.h>
#include <egnim/engine/physics/priv/physics_helper.h>
#include <egnim/engine/events/event_dispatcher.h>
#include <egnim/engine/events/contact_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics::priv {

/* ----------------------------- PhysicsWorldCallback ----------------------- */

PhysicsWorldCallback::PhysicsWorldCallback(events::EventDispatcher& event_dispatcher) :
  m_event_dispatcher(event_dispatcher)
{

}

void PhysicsWorldCallback::BeginContact(b2Contact* contact)
{
  auto event = events::BeginContactEvent(priv::PhysicsHelper::cast(*contact));
  m_event_dispatcher.dispatchEvent(event);
}

void PhysicsWorldCallback::EndContact(b2Contact* contact)
{
  auto event = events::EndContactEvent(priv::PhysicsHelper::cast(*contact));
  m_event_dispatcher.dispatchEvent(event);
}

void PhysicsWorldCallback::PreSolve(b2Contact* contact, const b2Manifold* old_manifold)
{
  auto event = events::PreSolveContactEvent(priv::PhysicsHelper::cast(*contact),
                                            priv::PhysicsHelper::cast(*old_manifold));
  m_event_dispatcher.dispatchEvent(event);
}

void PhysicsWorldCallback::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
  auto event = events::PostSolveContactEvent(priv::PhysicsHelper::cast(*contact),
                                             priv::PhysicsHelper::cast(*impulse));
  m_event_dispatcher.dispatchEvent(event);
}

/* ------------------------------ QueryAABBCallback ------------------------- */

PhysicsQueryAABBCallback::PhysicsQueryAABBCallback() :
  m_callback(nullptr)
{

}

PhysicsQueryAABBCallback::~PhysicsQueryAABBCallback() = default;

void PhysicsQueryAABBCallback::setCallback(const Callback* callback)
{
  m_callback = callback;
}

const PhysicsQueryAABBCallback::Callback* PhysicsQueryAABBCallback::getCallback()
{
  return m_callback;
}

bool PhysicsQueryAABBCallback::ReportFixture(b2Fixture* b2_fixture)
{
  auto first_shape = reinterpret_cast<PhysicsShape*>(b2_fixture->GetUserData().pointer);
  if(m_callback && *m_callback) return (*m_callback)(first_shape);
  else return false;
}

/* -------------------------------- RayCastCallback ------------------------- */

PhysicsRayCastCallback::PhysicsRayCastCallback() :
  m_callback(nullptr)
{

}

PhysicsRayCastCallback::~PhysicsRayCastCallback() = default;

void PhysicsRayCastCallback::setCallback(const Callback* callback)
{
  m_callback = callback;
}

const PhysicsRayCastCallback::Callback* PhysicsRayCastCallback::getCallback()
{
  return m_callback;
}

float PhysicsRayCastCallback::ReportFixture(b2Fixture* b2_fixture, const b2Vec2& b2_point,
                                            const b2Vec2& b2_normal, float fraction)
{
  auto first_shape = reinterpret_cast<PhysicsShape*>(b2_fixture->GetUserData().pointer);
  auto point = priv::PhysicsHelper::meter_to_pixel(b2_point);
  auto normal = priv::PhysicsHelper::meter_to_pixel(b2_normal);

  if(m_callback && *m_callback) return (*m_callback)(first_shape, point, normal, fraction);
  else return false;
}

} // namespace egnim::physics::priv