/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_fixture.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_edge_shape.h>
#include <box2d/b2_chain_shape.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_shape.h>
#include <egnim/engine/physics/physics_body.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

/* ------------------------------- PhysicsMaterial -------------------------- */

[[maybe_unused]] const PhysicsMaterial PhysicsMaterial::DefaultMaterial = PhysicsMaterial(0.1f, 0.5f, 0.5f);

PhysicsMaterial::PhysicsMaterial(float density, float restitution, float friction) noexcept :
  m_density(density),
  m_restitution(restitution),
  m_friction(friction)
{

}

void PhysicsMaterial::setDensity(float density)
{
  m_density = density;
}

void PhysicsMaterial::setRestitution(float restitution)
{
  m_restitution = restitution;
}

void PhysicsMaterial::setFriction(float friction)
{
  m_friction = friction;
}

float PhysicsMaterial::getDensity() const
{
  return m_density;
}

float PhysicsMaterial::getRestitution() const
{
  return m_restitution;
}

float PhysicsMaterial::getFriction() const
{
  return m_friction;
}

/* --------------------------------- PhysicsShape --------------------------- */

PhysicsShape::PhysicsShape(Type type, const PhysicsMaterial& physics_material) :
  m_physics_body(nullptr),
  m_b2_fixture(nullptr),
  m_type(type),
  m_physics_material(physics_material)
{

}

PhysicsShape::~PhysicsShape()
{
  destroyInternalFixture();
}

void PhysicsShape::setPhysicsMaterial(const PhysicsMaterial& physics_material)
{
  m_physics_material = physics_material;
  updateInternalFixture();
}

PhysicsMaterial PhysicsShape::getPhysicsMaterial()
{
  return m_physics_material;
}

void PhysicsShape::setDensity(float density)
{
  m_physics_material.setDensity(density);
  updateInternalFixture();
}
void PhysicsShape::setRestitution(float restitution)
{
  m_physics_material.setRestitution(restitution);
  updateInternalFixture();
}

void PhysicsShape::setFriction(float friction)
{
  m_physics_material.setFriction(friction);
  updateInternalFixture();
}

float PhysicsShape::getDensity() const
{
  return m_physics_material.getDensity();
}

float PhysicsShape::getRestitution() const
{
  return m_physics_material.getRestitution();
}

float PhysicsShape::getFriction() const
{
  return m_physics_material.getFriction();
}

PhysicsShape::Type PhysicsShape::getType() const
{
  return m_type;
}

PhysicsBody* PhysicsShape::getPhysicsBody()
{
  return m_physics_body;
}

const PhysicsBody* PhysicsShape::getPhysicsBody() const
{
  return m_physics_body;
}

void PhysicsShape::createInternalFixture()
{
  destroyInternalFixture();

  if(!getPhysicsBody())
    m_b2_fixture = nullptr;

  auto internal_shape = createInternalShape();
  assert(internal_shape);

  b2FixtureDef fixture_def;
  fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
  fixture_def.density = getDensity();
  fixture_def.friction = getFriction();
  fixture_def.restitution = getRestitution();
  fixture_def.shape = internal_shape.get();

  m_b2_fixture = getPhysicsBody()->createInternalFixture(&fixture_def);
}

void PhysicsShape::destroyInternalFixture()
{
  if(m_b2_fixture)
    getPhysicsBody()->destroyInternalFixture(m_b2_fixture);

  m_b2_fixture = nullptr;
}

void PhysicsShape::updateInternalFixture()
{
  if(m_b2_fixture)
  {
    m_b2_fixture->SetDensity(getDensity());
    m_b2_fixture->SetFriction(getFriction());
    m_b2_fixture->SetRestitution(getRestitution());
  }
}

void PhysicsShape::setPhysicsBody(PhysicsBody* physics_body)
{
  destroyInternalFixture();
  m_physics_body = physics_body;
  createInternalFixture();
}

/* ------------------------------ PhysicsShapeCircle ------------------------ */

PhysicsShapeCircle::PhysicsShapeCircle(float radius, const sf::Vector2f& offset,
                                       const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::Circle, physics_material),
  m_radius(radius),
  m_offset(offset)
{

}

std::unique_ptr<b2Shape> PhysicsShapeCircle::createInternalShape() const
{
  auto b2_circle_shape = std::make_unique<b2CircleShape>();
  b2_circle_shape->m_p.Set(m_offset.x, m_offset.y);
  b2_circle_shape->m_radius = m_radius;

  return b2_circle_shape;
}

float PhysicsShapeCircle::getRadius() const
{
  return m_radius;
}

const sf::Vector2f& PhysicsShapeCircle::getOffset() const
{
  return m_offset;
}

/* -------------------------------- PhysicsShapeBox ------------------------- */

PhysicsShapeBox::PhysicsShapeBox(const sf::Vector2f& size, const sf::Vector2f& offset,
                                 const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::Box, physics_material),
  m_size(size),
  m_offset(offset)
{

}

std::unique_ptr<b2Shape> PhysicsShapeBox::createInternalShape() const
{
  auto b2_box_shape = std::make_unique<b2PolygonShape>();
  b2_box_shape->SetAsBox(m_size.x, m_size.y, b2Vec2(m_offset.x, m_offset.y), 0);

  return b2_box_shape;
}

const sf::Vector2f& PhysicsShapeBox::getSize() const
{
  return m_size;
}

const sf::Vector2f& PhysicsShapeBox::getOffset() const
{
  return m_offset;
}

/* ------------------------------ PhysicsShapePolygon ----------------------- */

PhysicsShapePolygon::PhysicsShapePolygon(std::list<sf::Vector2f> points,
                                         const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::Polygon, physics_material),
  m_points(std::move(points))
{

}

std::unique_ptr<b2Shape> PhysicsShapePolygon::createInternalShape() const
{
  auto b2_polygon_shape = std::make_unique<b2PolygonShape>();
  auto b2_vertices = std::vector<b2Vec2>(m_points.size());
  auto b2_vec_index = 0;

  for(auto point : m_points)
    b2_vertices[b2_vec_index++].Set(point.x, point.y);

  b2_polygon_shape->Set(b2_vertices.data(), static_cast<int>(b2_vertices.size()));

  return b2_polygon_shape;
}

const std::list<sf::Vector2f>& PhysicsShapePolygon::getPoints() const
{
  return m_points;
}

/* --------------------------- PhysicsShapeEdgeSegment ---------------------- */

PhysicsShapeEdgeSegment::PhysicsShapeEdgeSegment(const sf::Vector2f& first, const sf::Vector2f& second,
                                                 const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::EdgeSegment, physics_material),
  m_first(first),
  m_second(second)
{

}

std::unique_ptr<b2Shape> PhysicsShapeEdgeSegment::createInternalShape() const
{
  auto b2_edge_shape = std::make_unique<b2EdgeShape>();
  b2_edge_shape->SetTwoSided(b2Vec2(m_first.x, m_first.y), b2Vec2(m_second.x, m_second.y));

  return b2_edge_shape;
}

const sf::Vector2f& PhysicsShapeEdgeSegment::getFirstPosition() const
{
  return m_first;
}

const sf::Vector2f& PhysicsShapeEdgeSegment::getSecondPosition() const
{
  return m_second;
}

/* ----------------------------- PhysicsShapeEdgeBox ------------------------ */

PhysicsShapeEdgeBox::PhysicsShapeEdgeBox(const sf::Vector2f& size, const sf::Vector2f& offset,
                                         const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::EdgeBox, physics_material),
  m_size(size),
  m_offset(offset)
{

}

std::unique_ptr<b2Shape> PhysicsShapeEdgeBox::createInternalShape() const
{
  auto b2_chain_shape = std::make_unique<b2ChainShape>();
  auto b2_vertices = std::array<b2Vec2, 4>();
  auto b2_offset = b2Vec2(m_offset.x, m_offset.y);

  b2_vertices[0] = b2Vec2(-0.5f, 0.5f) + b2_offset;
  b2_vertices[1] = b2Vec2(-0.5f, -0.5f) + b2_offset;
  b2_vertices[2] = b2Vec2(0.5f, -0.5f) + b2_offset;
  b2_vertices[3] = b2Vec2(0.5f, 0.5f) + b2_offset;

  b2_chain_shape->CreateLoop(b2_vertices.data(), 4);
  return b2_chain_shape;
}

const sf::Vector2f& PhysicsShapeEdgeBox::getSize() const
{
  return m_size;
}

const sf::Vector2f& PhysicsShapeEdgeBox::getOffset() const
{
  return m_offset;
}

/* ---------------------------- PhysicsShapeEdgePolygon --------------------- */

PhysicsShapeEdgePolygon::PhysicsShapeEdgePolygon(std::list<sf::Vector2f> points,
                                                 const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::EdgePolygon, physics_material),
  m_points(std::move(points))
{

}

std::unique_ptr<b2Shape> PhysicsShapeEdgePolygon::createInternalShape() const
{
  auto b2_chain_shape = std::make_unique<b2ChainShape>();
  auto b2_vertices = std::vector<b2Vec2>(m_points.size());
  auto b2_vec_index = 0;

  for(auto point : m_points)
    b2_vertices[b2_vec_index++].Set(point.x, point.y);

  b2_chain_shape->CreateLoop(b2_vertices.data(), static_cast<int>(b2_vertices.size()));

  return b2_chain_shape;
}

const std::list<sf::Vector2f>& PhysicsShapeEdgePolygon::getPoints() const
{
  return m_points;
}

/* ----------------------------- PhysicsShapeEdgeChain ---------------------- */

PhysicsShapeEdgeChain::PhysicsShapeEdgeChain(std::list<sf::Vector2f> points,
                                             const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::EdgeChain, physics_material),
  m_points(std::move(points))
{

}

std::unique_ptr<b2Shape> PhysicsShapeEdgeChain::createInternalShape() const
{
  auto b2_chain_shape = std::make_unique<b2ChainShape>();
  auto b2_vertices = std::vector<b2Vec2>(m_points.size());
  auto b2_vec_index = 0;

  for(auto point : m_points)
    b2_vertices[b2_vec_index++].Set(point.x, point.y);

  b2_chain_shape->CreateChain(b2_vertices.data(), static_cast<int>(b2_vertices.size()), b2_vertices.front(), b2_vertices.back());

  return b2_chain_shape;
}

const std::list<sf::Vector2f>& PhysicsShapeEdgeChain::getPoints() const
{
  return m_points;
}

} // namespace egnim::physics