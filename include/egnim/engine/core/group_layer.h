#ifndef GROUP_LAYER_H
#define GROUP_LAYER_H

/* --------------------------------- Standard ------------------------------- */
#include <list>
#include <memory>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/core/layer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
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

    [[nodiscard]] bool canMergeWith(const Layer& layer) const override;
    bool mergeWith(const Layer& layer) override;

  private:
    std::list<std::unique_ptr<Layer>> m_layers;
  };

} // namespace egnim::core

#endif //GROUP_LAYER_H
