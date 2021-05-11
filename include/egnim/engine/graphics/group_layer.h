#ifndef GROUP_LAYER_H
#define GROUP_LAYER_H

/* --------------------------------- Standard ------------------------------- */
#include <list>
#include <memory>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/graphics/layer.h>
#include <egnim/engine/graphics/group_layer_iterator.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics
{

  class EGNIM_UTILITY_API GroupLayer : public Layer
  {
  public:
    explicit GroupLayer();
    ~GroupLayer() override;

    void attachLayer(std::unique_ptr<Layer> layer);
    std::unique_ptr<Layer> detachLayer(const Layer& layer);
    [[nodiscard]] const std::list<std::unique_ptr<Layer>>& getLayers() const;

    [[nodiscard]] bool isEmpty() const override;
    [[nodiscard]] std::list<const Tileset*> getUsedTilesets() const override;
    [[nodiscard]] bool isUsedTileset(const Tileset& tileset) const override;

    [[nodiscard]] bool canMerge(const Layer& layer) const override;
    bool merge(const sf::Vector2u& point, const Layer& layer) override;

    [[nodiscard]] GroupLayerIterator begin();
    [[nodiscard]] ConstGroupLayerIterator begin() const;

    [[nodiscard]] GroupLayerIterator end();
    [[nodiscard]] ConstGroupLayerIterator end() const;

    [[nodiscard]] std::unique_ptr<Layer> clone() const override;

  private:
    std::list<std::unique_ptr<Layer>> m_layers;
  };

} // namespace egnim::graphics

#endif //GROUP_LAYER_H
