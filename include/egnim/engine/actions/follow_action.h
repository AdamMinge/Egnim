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

    void setMargins(float left_margin, float right_margin, float top_margin, float bottom_margin);

    void setLeftMargin(float left_margin);
    [[nodiscard]] float getLeftMargin() const;

    void setRightMargin(float right_margin);
    [[nodiscard]] float getRightMargin() const;

    void setTopMargin(float top_margin);
    [[nodiscard]] float getTopMargin() const;

    void setBottomMargin(float bottom_margin);
    [[nodiscard]] float getBottomMargin() const;

    void update(sf::Time dt) override;

    [[nodiscard]] bool isDone() const override;

    [[nodiscard]] std::unique_ptr<Action> clone() const override;

  private:
    scene::Node* m_followed_node;
    float m_left_margin;
    float m_right_margin;
    float m_top_margin;
    float m_bottom_margin;
  };

} // namespace egnim::actions

#endif //FOLLOW_ACTION_H
