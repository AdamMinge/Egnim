/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/node_factory.h>
#include <egnim/engine/core/node.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

std::unique_ptr<NodeFactory> NodeFactory::s_instance = nullptr;

NodeFactory::NodeFactory() = default;

NodeFactory::~NodeFactory() = default;

NodeFactory& NodeFactory::getInstance()
{
  if(!s_instance)
    s_instance = std::unique_ptr<NodeFactory>(new NodeFactory);
  return *s_instance;
}

bool NodeFactory::registerNode(std::string_view id, const NodeCreatorMetaInfo& creator_meta_info)
{
  if(isRegistered(id))
    return false;

  m_node_creators[id] = creator_meta_info;
  return true;
}

bool NodeFactory::unregisterNode(std::string_view id)
{
  if(!isRegistered(id))
    return false;

  m_node_creators.erase(id);
  return true;
}

bool NodeFactory::isRegistered(std::string_view id) const
{
  return m_node_creators.contains(id);
}

std::unique_ptr<Node> NodeFactory::createNode(std::string_view id) const
{
  if(isRegistered(id))
    return m_node_creators.at(id).creator();
  else
    return nullptr;
}

} // namespace egnim::core

