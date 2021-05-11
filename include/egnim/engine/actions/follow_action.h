#ifndef FOLLOW_ACTION_H
#define FOLLOW_ACTION_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/actions/action.h>
/* -------------------------------------------------------------------------- */

namespace egnim::actions
{

  class EGNIM_UTILITY_API FollowAction : public Action
  {
    EGNIM_CLASS(FollowAction, Action)

  public:
    explicit FollowAction(scene::Node* followed_node);
    ~FollowAction() override;

    void setFollowed(scene::Node* followed_node);
    [[nodiscard]] scene::Node* getFollowed() const;

    void setBoundary(const sf::FloatRect& rect);
    [[nodiscard]] const sf::FloatRect& getBoundary() const;

    void setOffset(const sf::Vector2f& offset);
    [[nodiscard]] const sf::Vector2f& getOffset() const;

    void update(sf::Time dt) override;

    [[nodiscard]] bool isDone() const override;

    [[nodiscard]] std::unique_ptr<Action> clone() const override;

  private:
    scene::Node* m_followed_node;
    sf::FloatRect m_rect;
    sf::Vector2f m_offset;
  };

} // namespace egnim::actions

#endif //FOLLOW_ACTION_H
