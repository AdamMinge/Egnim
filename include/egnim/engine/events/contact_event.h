#ifndef CONTACT_EVENT_H
#define CONTACT_EVENT_H

/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/events/event.h>
#include <egnim/engine/physics/physics_contact.h>
#include <egnim/engine/physics/physics_manifold.h>
#include <egnim/engine/physics/physics_contact_impulse.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class EGNIM_UTILITY_API ContactEvent: public Event
  {
    EGNIM_CLASS(ContactEvent, Event)

  public:
    ~ContactEvent() override;

    void setPhysicsContact(const physics::PhysicsContact& physics_contact);
    [[nodiscard]] const physics::PhysicsContact& getPhysicsContact() const;

  protected:
    explicit ContactEvent(const physics::PhysicsContact& physics_contact);

  private:
    physics::PhysicsContact m_physics_contact;
  };

  class EGNIM_UTILITY_API BeginContactEvent: public ContactEvent
  {
    EGNIM_CLASS(BeginContactEvent, ContactEvent)

  public:
    explicit BeginContactEvent(const physics::PhysicsContact& physics_contact);
    ~BeginContactEvent() override;
  };

  class EGNIM_UTILITY_API EndContactEvent: public ContactEvent
  {
    EGNIM_CLASS(EndContactEvent, ContactEvent)

  public:
    explicit EndContactEvent(const physics::PhysicsContact& physics_contact);
    ~EndContactEvent() override;
  };

  class EGNIM_UTILITY_API PreSolveContactEvent: public ContactEvent
  {
    EGNIM_CLASS(PreSolveContactEvent, ContactEvent)

  public:
    explicit PreSolveContactEvent(const physics::PhysicsContact& physics_contact,
                                  const physics::PhysicsManifold& physics_manifold);
    ~PreSolveContactEvent() override;

    void setPhysicsManifold(const physics::PhysicsManifold& physics_manifold);
    [[nodiscard]] const physics::PhysicsManifold& getPhysicsManifold() const;

  private:
    physics::PhysicsManifold m_physics_manifold;
  };

  class EGNIM_UTILITY_API PostSolveContactEvent: public ContactEvent
  {
    EGNIM_CLASS(PostSolveContactEvent, ContactEvent)

  public:
    explicit PostSolveContactEvent(const physics::PhysicsContact& physics_contact,
                                  const physics::PhysicsContactImpulse& physics_contact_impulse);
    ~PostSolveContactEvent() override;

    void setPhysicsContactImpulse(const physics::PhysicsContactImpulse& physics_contact_impulse);
    [[nodiscard]] const physics::PhysicsContactImpulse& getPhysicsContactImpulse() const;

  private:
    physics::PhysicsContactImpulse m_physics_contact_impulse;
  };

} // namespace egnim::events

#endif //CONTACT_EVENT_H
