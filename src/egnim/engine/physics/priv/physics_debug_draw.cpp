/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/priv/physics_debug_draw.h>
#include <egnim/engine/physics/priv/physics_helper.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics::priv {

PhysicsDebugDraw::PhysicsDebugDraw(sf::RenderTarget& render_target) :
  m_render_target(render_target)
{

}

PhysicsDebugDraw::~PhysicsDebugDraw() = default;

void PhysicsDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
  sf::ConvexShape polygon(vertexCount);
  for(int i = 0; i < vertexCount; i++)
  {
    auto transformedVec = priv::PhysicsHelper::meter_to_pixel(vertices[i]);
    polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y))); // flooring the coords to fix distorted lines on flat surfaces
  }																								   // they still show up though.. but less frequently
  polygon.setOutlineThickness(-1.f);
  polygon.setFillColor(sf::Color::Transparent);
  polygon.setOutlineColor(priv::PhysicsHelper::cast(color));

  m_render_target.draw(polygon);
}

void PhysicsDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
  sf::ConvexShape polygon(vertexCount);
  for(int i = 0; i < vertexCount; i++)
  {
    sf::Vector2f transformedVec = priv::PhysicsHelper::meter_to_pixel(vertices[i]);
    polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y))); // flooring the coords to fix distorted lines on flat surfaces
  }

  polygon.setOutlineThickness(-1.f);

  auto outline_color = priv::PhysicsHelper::cast(color);
  auto fill_color = outline_color;
  fill_color.a = 60;

  polygon.setFillColor(fill_color);
  polygon.setOutlineColor(outline_color);

  m_render_target.draw(polygon);
}

void PhysicsDebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
  sf::CircleShape circle(priv::PhysicsHelper::meter_to_pixel(radius));
  circle.setOrigin(priv::PhysicsHelper::meter_to_pixel(radius), priv::PhysicsHelper::meter_to_pixel(radius));
  circle.setPosition(priv::PhysicsHelper::meter_to_pixel(center));
  circle.setFillColor(sf::Color::Transparent);
  circle.setOutlineThickness(-1.f);
  circle.setOutlineColor(priv::PhysicsHelper::cast(color));

  m_render_target.draw(circle);
}

void PhysicsDebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
  sf::CircleShape circle(priv::PhysicsHelper::meter_to_pixel(radius));
  circle.setOrigin(priv::PhysicsHelper::meter_to_pixel(radius), priv::PhysicsHelper::meter_to_pixel(radius));
  circle.setPosition(priv::PhysicsHelper::meter_to_pixel(center));

  auto outline_color = priv::PhysicsHelper::cast(color);
  auto fill_color = outline_color;
  fill_color.a = 60;

  circle.setFillColor(fill_color);
  circle.setOutlineThickness(1.f);
  circle.setOutlineColor(outline_color);

  b2Vec2 endPoint = center + radius * axis;
  sf::Vertex line[2] =
    {
      sf::Vertex(priv::PhysicsHelper::meter_to_pixel(center), outline_color),
      sf::Vertex(priv::PhysicsHelper::meter_to_pixel(endPoint), outline_color),
    };

  m_render_target.draw(circle);
  m_render_target.draw(line, 2, sf::Lines);
}

void PhysicsDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
  sf::Vertex line[] = {
      sf::Vertex(priv::PhysicsHelper::meter_to_pixel(p1), priv::PhysicsHelper::cast(color)),
      sf::Vertex(priv::PhysicsHelper::meter_to_pixel(p2), priv::PhysicsHelper::cast(color))
  };

  m_render_target.draw(line, 2, sf::Lines);
}

void PhysicsDebugDraw::DrawTransform(const b2Transform& xf)
{
  float lineLength = 0.4;

  b2Vec2 xAxis = xf.p + lineLength * xf.q.GetXAxis();
  sf::Vertex redLine[] =
    {
      sf::Vertex(priv::PhysicsHelper::meter_to_pixel(xf.p), sf::Color::Red),
      sf::Vertex(priv::PhysicsHelper::meter_to_pixel(xAxis), sf::Color::Red)
    };

  b2Vec2 yAxis = xf.p + lineLength * xf.q.GetYAxis();
  sf::Vertex greenLine[] =
    {
      sf::Vertex(priv::PhysicsHelper::meter_to_pixel(xf.p), sf::Color::Green),
      sf::Vertex(priv::PhysicsHelper::meter_to_pixel(yAxis), sf::Color::Green)
    };

  m_render_target.draw(redLine, 2, sf::Lines);
  m_render_target.draw(greenLine, 2, sf::Lines);
}

void PhysicsDebugDraw::DrawPoint(const b2Vec2 &p, float size, const b2Color &color)
{
  sf::CircleShape circle(priv::PhysicsHelper::meter_to_pixel(size));
  circle.setOrigin(priv::PhysicsHelper::meter_to_pixel(size), priv::PhysicsHelper::meter_to_pixel(size));
  circle.setPosition(priv::PhysicsHelper::meter_to_pixel(p));
  circle.setFillColor(priv::PhysicsHelper::cast(color));
}

} // egnim::physics::priv

