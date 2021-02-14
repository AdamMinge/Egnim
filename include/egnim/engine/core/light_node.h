#ifndef LIGHT_NODE_H
#define LIGHT_NODE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  class LightNode : public Node
  {
  public:
    explicit LightNode();
    ~LightNode() override;

  };

} // namespace egnim::core

#endif //LIGHT_NODE_H
