#ifndef SCENE_NODE_H
#define SCENE_NODE_H

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
/* -------------------------------------------------------------------------- */

namespace core
{
  class Command;
  class CommandQueue;

  class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
  {
  public:
    explicit SceneNode();
    ~SceneNode() override;

    void attachChild(std::unique_ptr<SceneNode> node);
    std::unique_ptr<SceneNode> detachChild(const SceneNode& node);

    sf::Vector2f getWorldPosition() const;
    sf::Transform getWorldTransform() const;

    void update(CommandQueue& command_queue, sf::Time dt);
    void onCommand(const Command& command, sf::Time dt);

  protected:
    virtual void updateCurrent(CommandQueue& command_queue, sf::Time dt);
    void updateChildren(CommandQueue& command_queue, sf::Time dt);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


  private:
    std::vector<std::unique_ptr<SceneNode>> m_children;
    SceneNode* m_parent;
  };

}

#endif //SCENE_NODE_H
