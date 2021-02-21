/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/RenderTarget.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/label_node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

LabelNode::LabelNode() = default;

LabelNode::~LabelNode() = default;

void LabelNode::setFont(const sf::Font& font)
{
  m_label.setFont(font);
}

void LabelNode::setText(const sf::String& text)
{
  m_label.setString(text);
}

void LabelNode::setCharacterSize(unsigned size)
{
  m_label.setCharacterSize(size);
}

void LabelNode::setLineSpacing(float spacingFactory)
{
  m_label.setLineSpacing(spacingFactory);
}

void LabelNode::setLetterSpacing(float spacingFactory)
{
  m_label.setLetterSpacing(spacingFactory);
}

void LabelNode::setStyle(sf::Uint32 style)
{
  m_label.setStyle(style);
}

void LabelNode::setFillColor(const sf::Color& color)
{
  m_label.setFillColor(color);
}

void LabelNode::setOutlineColor(const sf::Color& color)
{
  m_label.setOutlineColor(color);
}

void LabelNode::setOutlineThickness(float thickness)
{
  m_label.setOutlineThickness(thickness);
}

const sf::Font& LabelNode::getFont() const
{
  return *m_label.getFont();
}

const sf::String& LabelNode::getText() const
{
  return m_label.getString();
}

unsigned LabelNode::getCharacterSize() const
{
  return m_label.getCharacterSize();
}

float LabelNode::getLineSpacing() const
{
  return m_label.getLineSpacing();
}

float LabelNode::getLetterSpacing() const
{
  return m_label.getLetterSpacing();
}

sf::Uint32 LabelNode::getStyle() const
{
  return m_label.getStyle();
}

const sf::Color& LabelNode::getFillColor() const
{
  return m_label.getFillColor();
}

const sf::Color& LabelNode::getOutlineColor() const
{
  return m_label.getOutlineColor();
}

float LabelNode::getOutlineThickness() const
{
  return m_label.getOutlineThickness();
}

void LabelNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(m_label);
}

} // namespace egnim::core