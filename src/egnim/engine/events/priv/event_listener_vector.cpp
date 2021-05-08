/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/priv/event_listener_vector.h>
#include <egnim/engine/events/event_listener.h>
#include <egnim/engine/scene/scene_node.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
/* -------------------------------------------------------------------------- */

namespace egnim::events::priv {

/* -------------------------- FixedListenerComparator ------------------------ */

bool FixedListenerComparator::operator()(const std::pair<int, EventListener*>& first_key,
  const std::pair<int, EventListener*>& second_key) const
{
  if(first_key.first < second_key.first)
    return true;

  return first_key.first == second_key.first && first_key.second < second_key.second;
}

/* ---------------------------- EventListenerVector -------------------------- */

EventListenerVector::EventListenerVector(EventDispatcher& event_dispatcher) :
  m_event_dispatcher(event_dispatcher)
{

}

EventListenerVector::~EventListenerVector() = default;

void EventListenerVector::append(EventListener* event_listener, scene::Node* node)
{
  assert(event_listener->getEventDispatcher() == nullptr);
  event_listener->setEventDispatcher(std::addressof(m_event_dispatcher));

  m_scene_graph_listeners.emplace_back(std::make_pair(node, event_listener));
}

void EventListenerVector::append(EventListener* event_listener, int fixed_priority)
{
  assert(event_listener->getEventDispatcher() == nullptr);
  event_listener->setEventDispatcher(std::addressof(m_event_dispatcher));

  auto& fixed_listener = fixed_priority < 0 ? m_lower_fixed_listeners : m_upper_fixed_listeners;
  fixed_listener.emplace(std::make_pair(fixed_priority, event_listener));
}

void EventListenerVector::remove(EventListener* event_listener)
{
  assert(event_listener->getEventDispatcher() == std::addressof(m_event_dispatcher));
  event_listener->setEventDispatcher(nullptr);

  auto remove_if = [&event_listener](auto&& pair){
    return pair.second == event_listener;
  };

  std::erase_if(m_lower_fixed_listeners, remove_if);
  std::erase_if(m_upper_fixed_listeners, remove_if);
  m_scene_graph_listeners.remove_if(remove_if);
}

void EventListenerVector::remove(scene::Node* node, bool recursive)
{
  m_scene_graph_listeners.remove_if([&node, this](auto&& pair){
    if(pair.first == node)
    {
      assert(pair.second->getEventDispatcher() == std::addressof(m_event_dispatcher));
      pair.second->setEventDispatcher(nullptr);
      return true;
    }

    return false;
  });
}

const EventListenerVector::FixedListeners& EventListenerVector::getLowerFixedListeners() const
{
  return m_lower_fixed_listeners;
}

const EventListenerVector::FixedListeners& EventListenerVector::getUpperFixedListeners() const
{
  return m_upper_fixed_listeners;
}

const EventListenerVector::SceneGraphListeners& EventListenerVector::getSceneGraphListeners() const
{
  return m_scene_graph_listeners;
}

size_t EventListenerVector::size() const
{
  return getLowerFixedListeners().size() +
        getUpperFixedListeners().size() +
        getSceneGraphListeners().size();
}

bool EventListenerVector::empty() const
{
  return size() == 0;
}

void EventListenerVector::clear()
{
  auto eventDispatcherSetter = [this](auto&& pair) {
    assert(pair.second->getEventDispatcher() == std::addressof(m_event_dispatcher));
    pair.second->setEventDispatcher(nullptr);
  };

  std::for_each(m_lower_fixed_listeners.begin(), m_lower_fixed_listeners.end(), eventDispatcherSetter);
  std::for_each(m_upper_fixed_listeners.begin(), m_upper_fixed_listeners.end(), eventDispatcherSetter);
  std::for_each(m_scene_graph_listeners.begin(), m_scene_graph_listeners.end(), eventDispatcherSetter);

  m_lower_fixed_listeners.clear();
  m_upper_fixed_listeners.clear();
  m_scene_graph_listeners.clear();
}

void EventListenerVector::sort()
{
  auto node_to_depth = getSceneGraphNodeDepth();
  m_scene_graph_listeners.sort([&node_to_depth](auto&& first_value, auto&& second_value){
    assert(node_to_depth.contains(first_value.first) && node_to_depth.contains(second_value.first));
    return node_to_depth[first_value.first] < node_to_depth[second_value.first];
  });
}

std::map<scene::Node*, int> EventListenerVector::getSceneGraphNodeDepth() const
{
  std::map<scene::Node*, int> node_to_depth;
  std::set<scene::Node*> node_to_do;

  for(auto& pair : getSceneGraphListeners())
    node_to_do.insert(pair.first);

  while(!node_to_do.empty())
  {
    auto scene_node = (*node_to_do.begin())->getScene();
    assert(scene_node);

    node_to_depth[scene_node] = 0;
    for(auto& node : *scene_node)
    {
      auto node_parent = node.getParent();
      assert(node_to_depth.contains(node_parent));
      node_to_depth[std::addressof(node)] = node_to_depth[node_parent] + 1;
      node_to_do.erase(std::addressof(node));
    }
  }

  return node_to_depth;
}

} // namespace egnim::events::priv
