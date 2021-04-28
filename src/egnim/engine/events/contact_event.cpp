/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/contact_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events {

/* -------------------------------- ContactEvent ----------------------------- */

ContactEvent::ContactEvent(const physics::PhysicsContact& physics_contact) :
  Event(Type::Physics),
  m_physics_contact(physics_contact)
{

}

ContactEvent::~ContactEvent() = default;

void ContactEvent::setPhysicsContact(const physics::PhysicsContact& physics_contact)
{
  m_physics_contact = physics_contact;
}

const physics::PhysicsContact& ContactEvent::getPhysicsContact() const
{
  return m_physics_contact;
}

/* ----------------------------- BeginContactEvent -------------------------- */

BeginContactEvent::BeginContactEvent(const physics::PhysicsContact& physics_contact) :
  ContactEvent(physics_contact)
{

}

BeginContactEvent::~BeginContactEvent() = default;

/* ------------------------------ EndContactEvent --------------------------- */

EndContactEvent::EndContactEvent(const physics::PhysicsContact& physics_contact) :
  ContactEvent(physics_contact)
{

}

EndContactEvent::~EndContactEvent() = default;

/* --------------------------- PreSolveContactEvent ------------------------- */

PreSolveContactEvent::PreSolveContactEvent(const physics::PhysicsContact& physics_contact,
                              const physics::PhysicsManifold& physics_manifold) :
  ContactEvent(physics_contact),
  m_physics_manifold(physics_manifold)
{

}

PreSolveContactEvent::~PreSolveContactEvent() = default;

void PreSolveContactEvent::setPhysicsManifold(const physics::PhysicsManifold& physics_manifold)
{
  m_physics_manifold = physics_manifold;
}

const physics::PhysicsManifold& PreSolveContactEvent::getPhysicsManifold() const
{
  return m_physics_manifold;
}

/* --------------------------- PostSolveContactEvent ------------------------ */

PostSolveContactEvent::PostSolveContactEvent(const physics::PhysicsContact& physics_contact,
                               const physics::PhysicsContactImpulse& physics_contact_impulse) :
  ContactEvent(physics_contact),
  m_physics_contact_impulse(physics_contact_impulse)
{

}

PostSolveContactEvent::~PostSolveContactEvent() = default;

void PostSolveContactEvent::setPhysicsContactImpulse(const physics::PhysicsContactImpulse& physics_contact_impulse)
{
  m_physics_contact_impulse = physics_contact_impulse;
}

const physics::PhysicsContactImpulse& PostSolveContactEvent::getPhysicsContactImpulse() const
{
  return m_physics_contact_impulse;
}

} // namespace egnim::events