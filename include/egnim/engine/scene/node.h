#ifndef NODE_H
#define NODE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <vector>
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/core/object.h>
#include <egnim/engine/scene/node_iterator.h>
/* -------------------------------------------------------------------------- */

namespace egnim::physics
{
  class PhysicsBody;
}

namespace egnim::scene
{
  class Component;
  class ComponentContainer;
  class SceneVisitor;
  class SceneNode;

  class EGNIM_UTILITY_API Node : public core::Object, public sf::Transformable, public sf::Drawable, private sf::NonCopyable
  {
    EGNIM_CLASS(Node, Object)

  public:
    ~Node() override;

    void attachChild(std::unique_ptr<Node> node);
    std::unique_ptr<Node> detachChild(const Node& node);
    [[nodiscard]] const std::vector<std::unique_ptr<Node>>& getChildren() const;

    void attachComponent(std::unique_ptr<Component> component);
    std::unique_ptr<Component> detachComponent(const Component& component);
    [[nodiscard]] const ComponentContainer& getComponentContainer() const;

    void setCameraMask(size_t mask, bool applyChildren = true);
    size_t getCameraMask() const;

    void setName(std::string_view name);
    std::string_view getName() const;

    [[nodiscard]] float getWorldRotation() const;
    [[nodiscard]] sf::Vector2f getWorldPosition() const;
    [[nodiscard]] sf::Transform getWorldTransform() const;

    [[nodiscard]] SceneNode* getScene();
    [[nodiscard]] Node* getParent();
    [[nodiscard]] Node* getRoot();

    [[nodiscard]] const physics::PhysicsBody* getPhysicsBody() const;
    [[nodiscard]] physics::PhysicsBody* getPhysicsBody();

    [[nodiscard]] NodeIterator begin();
    [[nodiscard]] ConstNodeIterator cbegin() const;

    [[nodiscard]] NodeIterator end();
    [[nodiscard]] ConstNodeIterator cend() const;

    template<typename TYPE>
    TYPE* findChildByName(std::string_view name);
    Node* findChildByName(std::string_view name);

    void update(sf::Time dt);

    virtual void accept(SceneVisitor& visitor) = 0;

  protected:
    explicit Node();

    virtual void updateCurrent(sf::Time dt);
    void updateChildren(sf::Time dt);
    void updateComponents(sf::Time dt);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

    bool isVisibleByTarget(sf::RenderTarget& target) const;

    void setParent(Node* parent);

  private:
    std::vector<std::unique_ptr<Node>> m_children;
    std::unique_ptr<ComponentContainer> m_components;
    Node* m_parent;
    size_t m_camera_mask;
    std::string_view m_name;
    physics::PhysicsBody* m_physics_body;
  };

  template<typename TYPE>
  TYPE* Node::findChildByName(std::string_view name)
  {
    return dynamic_cast<TYPE*>(findChildByName(name));
  }

} // namespace egnim::scene

#endif //NODE_H
