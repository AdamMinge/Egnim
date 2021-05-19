#ifndef PHYSICS_WORLD_CALLBACKS_H
#define PHYSICS_WORLD_CALLBACKS_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_world_callbacks.h>
/* --------------------------------- Standard ------------------------------- */
#include <functional>
/* -------------------------------------------------------------------------- */

namespace egnim
{
  namespace events { class EventDispatcher; };
  namespace physics { class PhysicsShape; }
}

namespace egnim::physics::priv
{

  class PhysicsWorldCallback : public b2ContactListener
  {
  public:
    explicit PhysicsWorldCallback(events::EventDispatcher& event_dispatcher);
    ~PhysicsWorldCallback() override = default;

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    void PreSolve(b2Contact* contact, const b2Manifold* old_manifold) override;
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

  private:
    events::EventDispatcher& m_event_dispatcher;
  };

  class PhysicsQueryAABBCallback : public b2QueryCallback
  {
    using Callback = std::function<bool(PhysicsShape*)>;

  public:
    explicit PhysicsQueryAABBCallback();
    ~PhysicsQueryAABBCallback() override;

    void setCallback(const Callback* callback);
    [[nodiscard]] const Callback* getCallback();

    bool ReportFixture(b2Fixture* b2_fixture) override;

  private:
    const Callback* m_callback;
  };

  class PhysicsRayCastCallback : public b2RayCastCallback
  {
    using Callback = std::function<float(PhysicsShape*, const sf::Vector2f&, const sf::Vector2f&, float)>;

  public:
    explicit PhysicsRayCastCallback();
    ~PhysicsRayCastCallback() override;

    void setCallback(const Callback* callback);
    [[nodiscard]] const Callback* getCallback();

    float ReportFixture(b2Fixture* b2_fixture, const b2Vec2& b2_point,
                        const b2Vec2& b2_normal, float fraction) override;

  private:
    const Callback* m_callback;
  };

} // namespace egnim::physics::priv

#endif //PHYSICS_WORLD_CALLBACKS_H
