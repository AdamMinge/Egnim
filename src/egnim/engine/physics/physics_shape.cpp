/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_fixture.h>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_shape.h>
#include <egnim/engine/physics/physics_body.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
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

b2Fixture* PhysicsShape::createInternalFixture()
{
  destroyInternalFixture();

  if(!getPhysicsBody())
    return nullptr;

  b2FixtureDef fixture_def;
  fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
  fixture_def.density = getDensity();
  fixture_def.friction = getFriction();
  fixture_def.restitution = getRestitution();
  fixture_def.shape = std::addressof(createInternalShape());

  return getPhysicsBody()->createInternalFixture(&fixture_def);
}

void PhysicsShape::destroyInternalFixture()
{
  if(getPhysicsBody())
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
  m_b2_fixture = createInternalFixture();
}

/* ------------------------------ PhysicsShapeCircle ------------------------ */

PhysicsShapeCircle::PhysicsShapeCircle(float radius,
                                       const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::Circle, physics_material),
  m_radius(radius)
{

}

b2Shape& PhysicsShapeCircle::createInternalShape() const
{

}

/* -------------------------------- PhysicsShapeBox ------------------------- */

PhysicsShapeBox::PhysicsShapeBox(const sf::Vector2f& size,
                                 const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::Box, physics_material),
  m_size(size)
{

}

b2Shape& PhysicsShapeBox::createInternalShape() const
{

}

/* ------------------------------ PhysicsShapePolygon ----------------------- */

PhysicsShapePolygon::PhysicsShapePolygon(std::list<sf::Vector2f> points,
                                         const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::Polygon, physics_material),
  m_points(std::move(points))
{

}

b2Shape& PhysicsShapePolygon::createInternalShape() const
{

}

/* --------------------------- PhysicsShapeEdgeSegment ---------------------- */

PhysicsShapeEdgeSegment::PhysicsShapeEdgeSegment(const sf::Vector2f& first, const sf::Vector2f& second,
                                                 const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::EdgeSegment, physics_material),
  m_first(first),
  m_second(second)
{

}

b2Shape& PhysicsShapeEdgeSegment::createInternalShape() const
{

}

/* ----------------------------- PhysicsShapeEdgeBox ------------------------ */

PhysicsShapeEdgeBox::PhysicsShapeEdgeBox(const sf::Vector2f& size,
                                         const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::EdgeBox, physics_material),
  m_size(size)
{

}

b2Shape& PhysicsShapeEdgeBox::createInternalShape() const
{

}

/* ---------------------------- PhysicsShapeEdgePolygon --------------------- */

PhysicsShapeEdgePolygon::PhysicsShapeEdgePolygon(std::list<sf::Vector2f> points,
                                                 const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::EdgePolygon, physics_material),
  m_points(std::move(points))
{

}

b2Shape& PhysicsShapeEdgePolygon::createInternalShape() const
{

}

/* ----------------------------- PhysicsShapeEdgeChain ---------------------- */

PhysicsShapeEdgeChain::PhysicsShapeEdgeChain(std::list<sf::Vector2f> points,
                                             const PhysicsMaterial& physics_material) :
  PhysicsShape(Type::EdgeChain, physics_material),
  m_points(std::move(points))
{

}

b2Shape& PhysicsShapeEdgeChain::createInternalShape() const
{

}

} // namespace egnim::physics