#ifndef TILE_MAP_H
#define TILE_MAP_H

/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  class EGNIM_UTILITY_API TileMap
  {
  public:
    enum class RenderOrder;

  };

  enum class TileMap::RenderOrder
  {
    RightDown,
    RightUp,
    LeftDown,
    LeftUp
  };

} // namespace egnim::core

#endif //TILE_MAP_H
