#ifndef LABEL_NODE_H
#define LABEL_NODE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <string_view>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  class LabelNode : public Node
  {
  public:
    explicit LabelNode(const sf::Font& font, const sf::String& text);
    ~LabelNode() override;

    void setFont(const sf::Font& font);
    void setText(const sf::String& text);
    void setCharacterSize(unsigned size);
    void setLineSpacing(float spacingFactory);
    void setLetterSpacing(float spacingFactory);
    void setStyle(sf::Uint32 style);
    void setFillColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);

    const sf::Font& getFont() const;
    const sf::String& getText() const;
    unsigned getCharacterSize() const;
    float getLineSpacing() const;
    float getLetterSpacing() const;
    sf::Uint32 getStyle() const;
    const sf::Color& getFillColor() const;
    const sf::Color& getOutlineColor() const;
    float getOutlineThickness() const;

  protected:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    sf::Text m_label;
  };

} // namespace egnim::core

#endif //LABEL_NODE_H
