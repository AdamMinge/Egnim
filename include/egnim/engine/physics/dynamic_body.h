#ifndef DYNAMIC_BODY_H
#define DYNAMIC_BODY_H

/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/physics/physics_body.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics
{

  class PhysicsWorld;

  class DynamicBody : public PhysicsBody
  {
  public:
    explicit DynamicBody(PhysicsWorld& physics_world);
    ~DynamicBody() override;

  protected:
    void init();
  };

}

#endif //DYNAMIC_BODY_H
