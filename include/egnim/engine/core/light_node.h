#ifndef LIGHT_NODE_H
#define LIGHT_NODE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/node.h>
#include <egnim/engine/core/node_factory.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  class LightNode : public Node, public RegisteredInNodeFactory<LightNode>
  {
    EGNIM_CLASS(LightNode, Node)

  public:
    explicit LightNode();
    ~LightNode() override;

  };

} // namespace egnim::core

#endif //LIGHT_NODE_H
