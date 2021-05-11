#ifndef ACTION_H
#define ACTION_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Time.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/core/object.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{
  class Node;
}

namespace egnim::actions
{

  class ActionManager;

  class EGNIM_UTILITY_API Action : public core::Object
  {
    EGNIM_CLASS(Action, Object)
    friend ActionManager;

  public:
    explicit Action();
    ~Action() override;

    [[nodiscard]] scene::Node* getTarget() const;

    virtual void update(sf::Time dt);

    [[nodiscard]] virtual bool isDone() const;

    [[nodiscard]] virtual std::unique_ptr<Action> getReverse() const = 0;
    [[nodiscard]] virtual bool isReversible() const = 0;

    [[nodiscard]] virtual std::unique_ptr<Action> clone() const = 0;

  protected:
    void setTarget(scene::Node* target);

  private:
    scene::Node* m_target;
  };

} // namespace egnim::actions

#endif //ACTION_H
