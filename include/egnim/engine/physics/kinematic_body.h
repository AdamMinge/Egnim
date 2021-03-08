#ifndef KINEMATIC_BODY_H
#define KINEMATIC_BODY_H

/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/physics/physics_body.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics
{

  class PhysicsWorld;

  class KinematicBody : public PhysicsBody
  {
  public:
    explicit KinematicBody(PhysicsWorld& physics_world);
    ~KinematicBody() override;

  protected:
    void init();
  };

}

#endif //KINEMATIC_BODY_H
