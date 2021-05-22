#ifndef NODE_FACTORY_H
#define NODE_FACTORY_H


/* --------------------------------- Standard ------------------------------- */
#include <string_view>
#include <functional>
#include <memory>
#include <map>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{
  class Node;

  class EGNIM_UTILITY_API NodeFactory
  {
  public:
    struct NodeCreatorMetaInfo;

  public:
    ~NodeFactory();

    static NodeFactory& getInstance();

    bool registerNode(std::string_view id, const NodeCreatorMetaInfo& creator_meta_info);
    bool unregisterNode(std::string_view id);

    [[nodiscard]] bool isRegistered(std::string_view id) const;

    [[nodiscard]] std::unique_ptr<Node> createNode(std::string_view id) const;

  private:
    explicit NodeFactory();

  private:
    static std::unique_ptr<NodeFactory> s_instance;
    std::map<std::string_view, NodeCreatorMetaInfo> m_node_creators;
  };

  struct NodeFactory::NodeCreatorMetaInfo
  {
    using NodeCreator = std::function<std::unique_ptr<Node>()>;

    NodeCreator creator;
  };

  template<typename TYPE>
  class RegisteredInNodeFactory
  {
  private:
    [[maybe_unused]] static const bool s_registered;

  protected:
    RegisteredInNodeFactory() { s_registered; }
    static bool isRegistered() { return s_registered; }
  };

  template<typename TYPE>
  [[maybe_unused]] const bool RegisteredInNodeFactory<TYPE>::s_registered = NodeFactory::getInstance().registerNode(
    TYPE::staticClassName(), { std::function<std::unique_ptr<Node>()>([](){ return TYPE::create(); }) });

} // namespace egnim::scene

#endif //NODE_FACTORY_H
