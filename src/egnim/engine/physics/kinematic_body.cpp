/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_body.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/kinematic_body.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

KinematicBody::KinematicBody(PhysicsWorld& physics_world) :
  PhysicsBody(physics_world)
{
  init();
}

KinematicBody::~KinematicBody() = default;

void KinematicBody::init()
{
  b2BodyDef b2_body_def;
  createBody(b2_body_def);
}

} // namespace egnim::physics