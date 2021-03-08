#ifndef STATIC_BODY_H
#define STATIC_BODY_H

/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/physics/physics_body.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics
{

  class PhysicsWorld;

  class StaticBody : public PhysicsBody
  {
  public:
    explicit StaticBody(PhysicsWorld& physics_world);
    ~StaticBody() override;

  protected:
    void init();
  };

}

#endif //STATIC_BODY_H
