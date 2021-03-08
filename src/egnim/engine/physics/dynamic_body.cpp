/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_body.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/dynamic_body.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

DynamicBody::DynamicBody(PhysicsWorld& physics_world) :
  PhysicsBody(physics_world)
{
  init();
}

DynamicBody::~DynamicBody() = default;

void DynamicBody::init()
{
  b2BodyDef b2_body_def;
  createBody(b2_body_def);
}

} // namespace egnim::physics