#ifndef COMMAND_H
#define COMMAND_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Time.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <functional>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{
  class Node;

  class Command
  {
  public:
    explicit Command() = default;
    virtual ~Command() = default;

    virtual void operator()(Node& node, sf::Time dt) const = 0;
  };

  template<typename NODE_TYPE>
  class BaseCommand : public Command
  {
  public:
    explicit BaseCommand() = default;
    ~BaseCommand() override = default;

    void operator()(Node& node, sf::Time) const override;

  protected:
    virtual void action(NODE_TYPE& node, sf::Time) const;
  };

  template<typename NODE_TYPE>
  class FunctionCommand : public BaseCommand<NODE_TYPE>
  {
  public:
    explicit FunctionCommand(std::function<void(NODE_TYPE& node, sf::Time)> action);
    ~FunctionCommand() override = default;

  protected:
    void action(NODE_TYPE& node, sf::Time) const override;

  private:
    std::function<void(NODE_TYPE& node, sf::Time)> m_action;
  };

  /* -------------------------------- BaseCommand ----------------------------- */

  template<typename NODE_TYPE>
  void BaseCommand<NODE_TYPE>::operator()(Node &node, sf::Time dt) const
  {
    if(auto casted_node = dynamic_cast<NODE_TYPE*>(&node); casted_node)
      action(*casted_node, dt);
  }

  template<typename NODE_TYPE>
  void BaseCommand<NODE_TYPE>::action(NODE_TYPE& node, sf::Time dt) const {}

  /* ------------------------------ FunctionCommand --------------------------- */

  template<typename NODE_TYPE>
  FunctionCommand<NODE_TYPE>::FunctionCommand(std::function<void(NODE_TYPE &, sf::Time)> action) :
    m_action(std::move(action))
  {

  }

  template<typename NODE_TYPE>
  void FunctionCommand<NODE_TYPE>::action(NODE_TYPE& node, sf::Time dt) const
  {
    m_action(node, dt);
  }

} // namespace egnim::core

#endif //COMMAND_H
