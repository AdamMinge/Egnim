/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/tile_map_node.h>
#include <egnim/engine/scene/scene_visitor.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

TileMapNode::TileMapNode() :
  m_tile_map(graphics::TileMap::Orientation::Orthogonal,
             graphics::TileMap::RenderOrder::LeftDown,
             sf::Vector2u(32, 32))
{

}

TileMapNode::~TileMapNode() = default;

graphics::TileMap& TileMapNode::getTileMap()
{
  return m_tile_map;
}

const graphics::TileMap& TileMapNode::getTileMap() const
{
  return m_tile_map;
}

void TileMapNode::accept(SceneVisitor& visitor)
{
  visitor.visitTileMapNode(*this);
}

std::unique_ptr<Node> TileMapNode::clone() const
{
  auto clone_node = std::make_unique<TileMapNode>();
  Node::initializeClone(*clone_node);
  static_assert(false, "TileMapNode clone : Not implemented yet");

  return clone_node;
}

void TileMapNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_tile_map, states);
}

} // namespace egnim::scene