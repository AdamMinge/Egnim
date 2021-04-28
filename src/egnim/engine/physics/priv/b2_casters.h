#ifndef B2_CASTERS_H
#define B2_CASTERS_H

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

} // namespace egnim::physics::priv

#endif //B2_CASTERS_H
