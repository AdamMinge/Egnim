/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_body.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/static_body.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

StaticBody::StaticBody(PhysicsWorld& physics_world) :
  PhysicsBody(physics_world)
{
  init();
}

StaticBody::~StaticBody() = default;

void StaticBody::init()
{
  b2BodyDef b2_body_def;
  createBody(b2_body_def);
}

} // namespace egnim::physics