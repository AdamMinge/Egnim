/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_fixture.h>
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

PhysicsShapeCircle::PhysicsShapeCircle(float radius,
                                       const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::Circle, physics_material),
  m_radius(radius)
{

}

std::unique_ptr<b2Shape> PhysicsShapeCircle::createInternalShape() const
{

}

void PhysicsShapeCircle::setRadius(float radius)
{
  m_radius = radius;
  createInternalFixture();
}

float PhysicsShapeCircle::getRadius() const
{
  return m_radius;
}

/* -------------------------------- PhysicsShapeBox ------------------------- */

PhysicsShapeBox::PhysicsShapeBox(const sf::Vector2f& size,
                                 const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::Box, physics_material),
  m_size(size)
{

}

std::unique_ptr<b2Shape> PhysicsShapeBox::createInternalShape() const
{

}

void PhysicsShapeBox::setSize(const sf::Vector2f& size)
{
  m_size = size;
  createInternalFixture();
}

const sf::Vector2f& PhysicsShapeBox::getSize() const
{
  return m_size;
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

}

void PhysicsShapePolygon::setPoints(std::list<sf::Vector2f> points)
{
  m_points = std::move(points);
  createInternalFixture();
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

}

void PhysicsShapeEdgeSegment::setPositions(const sf::Vector2f& first, const sf::Vector2f& second)
{
  m_first = first;
  m_second = second;
  createInternalFixture();
}

void PhysicsShapeEdgeSegment::setFirstPosition(const sf::Vector2f& first)
{
  setPositions(first, getSecondPosition());
}

void PhysicsShapeEdgeSegment::setSecondPosition(const sf::Vector2f& second)
{
  setPositions(getFirstPosition(), second);
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

PhysicsShapeEdgeBox::PhysicsShapeEdgeBox(const sf::Vector2f& size,
                                         const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::EdgeBox, physics_material),
  m_size(size)
{

}

std::unique_ptr<b2Shape> PhysicsShapeEdgeBox::createInternalShape() const
{

}

void PhysicsShapeEdgeBox::setSize(const sf::Vector2f& size)
{
  m_size = size;
  createInternalFixture();
}

const sf::Vector2f& PhysicsShapeEdgeBox::getSize() const
{
  return m_size;
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

}

void PhysicsShapeEdgePolygon::setPoints(std::list<sf::Vector2f> points)
{
  m_points = std::move(points);
  createInternalFixture();
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

}

void PhysicsShapeEdgeChain::setPoints(std::list<sf::Vector2f> points)
{
  m_points = std::move(points);
  createInternalFixture();
}

const std::list<sf::Vector2f>& PhysicsShapeEdgeChain::getPoints() const
{
  return m_points;
}

} // namespace egnim::physics