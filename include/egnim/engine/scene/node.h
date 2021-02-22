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
#include <egnim/engine/core/object.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{
  class Command;
  class CommandQueue;
}

namespace egnim::scene
{
  class Component;
  class ComponentContainer;

  class Node : public core::Object, public sf::Transformable, public sf::Drawable, private sf::NonCopyable
  {
    EGNIM_CLASS(Node, Object)

  public:
    ~Node() override;

    void attachChild(std::unique_ptr<Node> node);
    std::unique_ptr<Node> detachChild(const Node& node);

    void attachComponent(std::unique_ptr<Component> component);
    std::unique_ptr<Component> attachComponent(const Component& component);

    void setCameraMask(size_t mask, bool applyChildren = true);
    size_t getCameraMask() const;

    sf::Vector2f getWorldPosition() const;
    sf::Transform getWorldTransform() const;

    void update(core::CommandQueue& command_queue, sf::Time dt);
    void onCommand(const core::Command& command, sf::Time dt);

  protected:
    explicit Node();

    virtual void updateCurrent(core::CommandQueue& command_queue, sf::Time dt);
    void updateChildren(core::CommandQueue& command_queue, sf::Time dt);
    void updateComponents(sf::Time dt);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

    bool isVisibleByTarget(sf::RenderTarget& target) const;

  private:
    std::vector<std::unique_ptr<Node>> m_children;
    std::unique_ptr<ComponentContainer> m_components;
    Node* m_parent;
    size_t m_camera_mask;
  };

} // namespace egnim::scene

#endif //NODE_H
