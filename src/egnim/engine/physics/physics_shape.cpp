/* ----------------------------------- Box2d -------------------------------- */
#include <box2d/b2_fixture.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_edge_shape.h>
#include <box2d/b2_chain_shape.h>
/* --------------------------------- Standard ------------------------------- */
#include <vector>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/physics/physics_shape.h>
#include <egnim/engine/physics/physics_body.h>
#include <egnim/engine/physics/priv/physics_helper.h>
#include <egnim/engine/math/vector_helper.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics {

/* --------------------------------- PhysicsShape --------------------------- */

PhysicsShape::PhysicsShape(Type type, const PhysicsMaterial& physics_material) :
  m_physics_body(nullptr),
  m_b2_fixture(nullptr),
  m_type(type),
  m_physics_material(physics_material),
  m_contact_test_bitmask(0x0001),
  m_collision_bitmask(0xFFFF),
  m_group_index(0),
  m_sensor(false)
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

PhysicsMaterial PhysicsShape::getPhysicsMaterial() const
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

void PhysicsShape::setRestitutionThreshold(float threshold)
{
  m_physics_material.setRestitutionThreshold(threshold);
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

float PhysicsShape::getRestitutionThreshold() const
{
  return m_physics_material.getRestitutionThreshold();
}

void PhysicsShape::setContactTestBitmask(std::uint16_t bitmask)
{
  m_contact_test_bitmask = bitmask;
  updateInternalFixture();
}

std::uint16_t PhysicsShape::getContactTestBitmask() const
{
  return m_contact_test_bitmask;
}

void PhysicsShape::setCollisionBitmask(std::uint16_t bitmask)
{
  m_collision_bitmask = bitmask;
  updateInternalFixture();
}

std::uint16_t PhysicsShape::getCollisionBitmask() const
{
  return m_collision_bitmask;
}

void PhysicsShape::setGroup(std::int16_t group)
{
  m_group_index = group;
  updateInternalFixture();
}

std::int16_t PhysicsShape::getGroup() const
{
  return m_group_index;
}

void PhysicsShape::setSensor(bool sensor)
{
  m_sensor = sensor;
  updateInternalFixture();
}

bool PhysicsShape::isSensor() const
{
  return m_sensor;
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
  if(m_physics_body && m_physics_body->m_b2_body)
  {
    auto internal_shape = createInternalShape();
    assert(internal_shape);

    b2FixtureDef fixture_def;
    fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
    fixture_def.density = getDensity();
    fixture_def.friction = getFriction();
    fixture_def.restitution = getRestitution();
    fixture_def.shape = internal_shape.get();
    fixture_def.filter.categoryBits = m_contact_test_bitmask;
    fixture_def.filter.maskBits = m_collision_bitmask;
    fixture_def.filter.groupIndex = m_group_index;
    fixture_def.isSensor = m_sensor;

    assert(!m_b2_fixture);
    m_b2_fixture = m_physics_body->createInternalFixture(&fixture_def);
  }
}

void PhysicsShape::destroyInternalFixture()
{
  if(m_physics_body && m_physics_body->m_b2_body)
  {
    assert(m_b2_fixture);
    getPhysicsBody()->destroyInternalFixture(m_b2_fixture);
    m_b2_fixture = nullptr;
  }
}

void PhysicsShape::updateInternalFixture()
{
  if(m_b2_fixture)
  {
    m_b2_fixture->SetDensity(getDensity());
    m_b2_fixture->SetFriction(getFriction());
    m_b2_fixture->SetRestitution(getRestitution());

    b2Filter b2_filter;
    b2_filter.categoryBits = getContactTestBitmask();
    b2_filter.maskBits = getCollisionBitmask();
    b2_filter.groupIndex = getGroup();

    m_b2_fixture->SetFilterData(b2_filter);
    m_b2_fixture->SetSensor(isSensor());
  }
}

void PhysicsShape::onEnter()
{
  m_physics_body = dynamic_cast<PhysicsBody*>(getOwner());
  createInternalFixture();
}

void PhysicsShape::onExit()
{
  destroyInternalFixture();
  m_physics_body = nullptr;
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
  auto b2_offset = priv::PhysicsHelper::pixel_to_meter(m_offset);
  b2_circle_shape->m_p.Set(b2_offset.x, b2_offset.y);
  b2_circle_shape->m_radius = priv::PhysicsHelper::pixel_to_meter(m_radius);

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

int32_t PhysicsShapeCircle::getChildCount() const
{
  return 1;
}

PhysicsMass PhysicsShapeCircle::getMass() const
{
  PhysicsMass mass;
  mass.setMass(getDensity() * b2_pi * getRadius() * getRadius());
  mass.setCenter(getOffset());
  mass.setRotationalInertia(mass.getMass() * (0.5f * getRadius() * getRadius() +
                            math::VectorHelper::dot(getOffset(), getOffset())));

  return mass;
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
  auto b2_size = priv::PhysicsHelper::pixel_to_meter(m_size);
  auto b2_offset = priv::PhysicsHelper::pixel_to_meter(m_offset);
  b2_box_shape->SetAsBox(b2_size.x / 2.0f, b2_size.y / 2.0f, b2_offset, 0);

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

int32_t PhysicsShapeBox::getChildCount() const
{
  return 1;
}

PhysicsMass PhysicsShapeBox::getMass() const
{
  sf::Vector2f vertices[] = {
    sf::Vector2f(-m_size.x / 2.0f, -m_size.x / 2.0f),
    sf::Vector2f(m_size.x / 2.0f, -m_size.x / 2.0f),
    sf::Vector2f(m_size.x / 2.0f, m_size.x / 2.0f),
    sf::Vector2f(-m_size.x / 2.0f, m_size.x / 2.0f)
  };

  auto center = sf::Vector2f(0.0f, 0.0f);
  auto area = 0.0f;
  auto I = 0.0f;

  auto s = vertices[0];
  auto k_inv3 = 1.0f / 3.0f;

  for (int32 i = 0; i < 4; ++i)
  {
    auto e1 = vertices[i] - s;
    auto e2 = i + 1 < 4 ? vertices[i+1] - s : vertices[0] - s;

    float D = math::VectorHelper::cross(e1, e2);

    float triangleArea = 0.5f * D;
    area += triangleArea;

    center += triangleArea * k_inv3 * (e1 + e2);

    float ex1 = e1.x, ey1 = e1.y;
    float ex2 = e2.x, ey2 = e2.y;

    float int_x2 = ex1*ex1 + ex2*ex1 + ex2*ex2;
    float int_y2 = ey1*ey1 + ey2*ey1 + ey2*ey2;

    I += (0.25f * k_inv3 * D) * (int_x2 + int_y2);
  }

  center *= 1.0f / area;

  PhysicsMass mass;
  mass.setMass(getDensity() * area);
  mass.setCenter(center + s);
  mass.setRotationalInertia(
    (getDensity() * I) + (mass.getMass() * math::VectorHelper::dot(mass.getCenter(), mass.getCenter()) -
                                math::VectorHelper::dot(center, center)));

  return mass;
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
  {
    auto b2_point = priv::PhysicsHelper::pixel_to_meter(point);
    b2_vertices[b2_vec_index++].Set(b2_point.x, b2_point.y);
  }

  b2_polygon_shape->Set(b2_vertices.data(), static_cast<int>(b2_vertices.size()));

  return b2_polygon_shape;
}

const std::list<sf::Vector2f>& PhysicsShapePolygon::getPoints() const
{
  return m_points;
}

int32_t PhysicsShapePolygon::getChildCount() const
{
  return 1;
}

PhysicsMass PhysicsShapePolygon::getMass() const
{
  sf::Vector2f ps[b2_maxPolygonVertices];
  sf::Vector2f vertices[b2_maxPolygonVertices];
  auto vertices_count = 0;

  int32 tempCount = 0;

  for(auto& point : m_points)
  {
    auto v = point;
    bool unique = true;

    for (int32 j = 0; j < tempCount; ++j)
    {
      auto c = v - ps[j];
      if (math::VectorHelper::dot(c, c) < ((0.5f * b2_linearSlop) * (0.5f * b2_linearSlop)))
      {
        unique = false;
        break;
      }
    }

    if (unique)
      ps[tempCount++] = v;
  }

  int32 i0 = 0;
  auto x0 = ps[0].x;
  for (int32 i = 1; i < m_points.size(); ++i)
  {
    auto x = ps[i].x;
    if (x > x0 || (x == x0 && ps[i].y < ps[i0].y))
    {
      i0 = i;
      x0 = x;
    }
  }

  int32 hull[b2_maxPolygonVertices];
  auto m = 0;
  auto ih = i0;

  for (;;)
  {
    b2Assert(m < b2_maxPolygonVertices);
    hull[m] = ih;

    int32 ie = 0;
    for (int32 j = 1; j < m_points.size(); ++j)
    {
      if (ie == ih)
      {
        ie = j;
        continue;
      }

      auto r = ps[ie] - ps[hull[m]];
      auto v = ps[j] - ps[hull[m]];
      float c = math::VectorHelper::cross(r, v);
      if (c < 0.0f)
      {
        ie = j;
      }

      auto v_length_squared = v.x * v.x + v.y * v.y;
      auto r_length_squared = v.x * v.x + v.y * v.y;

      if (c == 0.0f && v_length_squared > r_length_squared)
        ie = j;
    }

    ++m;
    ih = ie;

    if (ie == i0)
      break;
  }

  vertices_count = m;
  for (int32 i = 0; i < vertices_count; ++i)
    vertices[i] = ps[hull[i]];

  auto center = sf::Vector2f(0.0f, 0.0f);
  float area = 0.0f;
  float I = 0.0f;

  auto s = vertices[0];
  const float k_inv3 = 1.0f / 3.0f;

  for (int32 i = 0; i < vertices_count; ++i)
  {
    auto e1 = vertices[i] - s;
    auto e2 = i + 1 < vertices_count ? vertices[i+1] - s : vertices[0] - s;

    float D = math::VectorHelper::cross(e1, e2);

    float triangleArea = 0.5f * D;
    area += triangleArea;

    center += triangleArea * k_inv3 * (e1 + e2);

    float ex1 = e1.x, ey1 = e1.y;
    float ex2 = e2.x, ey2 = e2.y;

    float int_x2 = ex1*ex1 + ex2*ex1 + ex2*ex2;
    float int_y2 = ey1*ey1 + ey2*ey1 + ey2*ey2;

    I += (0.25f * k_inv3 * D) * (int_x2 + int_y2);
  }

  center *= 1.0f / area;

  PhysicsMass mass;
  mass.setMass(getDensity() * area);
  mass.setCenter(center + s);
  mass.setRotationalInertia(
    (getDensity() * I) + (mass.getMass() * math::VectorHelper::dot(mass.getCenter(), mass.getCenter()) -
      math::VectorHelper::dot(center, center)));

  return mass;
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
  b2_edge_shape->SetTwoSided(priv::PhysicsHelper::pixel_to_meter(m_first),
                             priv::PhysicsHelper::pixel_to_meter(m_second));

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

int32_t PhysicsShapeEdgeSegment::getChildCount() const
{
  return 1;
}

PhysicsMass PhysicsShapeEdgeSegment::getMass() const
{
  PhysicsMass mass;
  mass.setMass(0.f);
  mass.setCenter(0.5f * (m_first + m_second));
  mass.setRotationalInertia(0.f);

  return mass;
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
  auto b2_offset = priv::PhysicsHelper::pixel_to_meter(m_offset);
  auto b2_size = priv::PhysicsHelper::pixel_to_meter(m_size);

  b2_vertices[0] = b2Vec2(-0.5f * b2_size.x / 2.f, 0.5f * b2_size.x / 2.f) + b2_offset;
  b2_vertices[1] = b2Vec2(-0.5f * b2_size.x / 2.f, -0.5f * b2_size.x / 2.f) + b2_offset;
  b2_vertices[2] = b2Vec2(0.5f * b2_size.x / 2.f, -0.5f * b2_size.x / 2.f) + b2_offset;
  b2_vertices[3] = b2Vec2(0.5f * b2_size.x / 2.f, 0.5f * b2_size.x / 2.f) + b2_offset;

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

int32_t PhysicsShapeEdgeBox::getChildCount() const
{
  return 5;
}

PhysicsMass PhysicsShapeEdgeBox::getMass() const
{
  PhysicsMass mass;
  mass.setMass(0.f);
  mass.setCenter(sf::Vector2f(0.f, 0.f));
  mass.setRotationalInertia(0.f);

  return mass;
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
  {
    auto b2_point = priv::PhysicsHelper::pixel_to_meter(point);
    b2_vertices[b2_vec_index++].Set(b2_point.x, b2_point.y);
  }

  b2_chain_shape->CreateLoop(b2_vertices.data(), static_cast<int>(b2_vertices.size()));

  return b2_chain_shape;
}

const std::list<sf::Vector2f>& PhysicsShapeEdgePolygon::getPoints() const
{
  return m_points;
}

int32_t PhysicsShapeEdgePolygon::getChildCount() const
{
  return static_cast<int32_t>(m_points.size()) + 1;
}

PhysicsMass PhysicsShapeEdgePolygon::getMass() const
{
  PhysicsMass mass;
  mass.setMass(0.f);
  mass.setCenter(sf::Vector2f(0.f, 0.f));
  mass.setRotationalInertia(0.f);

  return mass;
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
  {
    auto b2_point = priv::PhysicsHelper::pixel_to_meter(point);
    b2_vertices[b2_vec_index++].Set(b2_point.x, b2_point.y);
  }

  b2_chain_shape->CreateChain(b2_vertices.data(), static_cast<int>(b2_vertices.size()), b2_vertices.front(), b2_vertices.back());

  return b2_chain_shape;
}

const std::list<sf::Vector2f>& PhysicsShapeEdgeChain::getPoints() const
{
  return m_points;
}

int32_t PhysicsShapeEdgeChain::getChildCount() const
{
  return static_cast<int32_t>(m_points.size());
}

PhysicsMass PhysicsShapeEdgeChain::getMass() const
{
  PhysicsMass mass;
  mass.setMass(0.f);
  mass.setCenter(sf::Vector2f(0.f, 0.f));
  mass.setRotationalInertia(0.f);

  return mass;
}

} // namespace egnim::physics