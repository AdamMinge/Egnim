/* --------------------------------- Standard ------------------------------- */
#include <bitset>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/event_dispatcher.h>
#include <egnim/engine/events/event.h>
#include <egnim/engine/events/event_listener.h>
#include <egnim/engine/events/priv/event_listener_vector.h>
/* -------------------------------------------------------------------------- */

namespace egnim::event {

EventDispatcher::EventDispatcher() :
  m_enabled(true)
{

}

EventDispatcher::~EventDispatcher() = default;

void EventDispatcher::addEventListener(EventListener* event_listener, scene::Node* node)
{
  visitEventListenerVectors(event_listener->getListenEvents(), [&event_listener, &node](auto& listener_vector){
    listener_vector.append(event_listener, node);
  });
}

void EventDispatcher::addEventListener(EventListener* event_listener, int fixed_priority)
{
  visitEventListenerVectors(event_listener->getListenEvents(), [&event_listener, &fixed_priority](auto& listener_vector){
    listener_vector.append(event_listener, fixed_priority);
  });
}

void EventDispatcher::removeEventListener(EventListener* event_listener)
{
  visitEventListenerVectors(event_listener->getListenEvents(), [&event_listener](auto& listener_vector){
    listener_vector.remove(event_listener);
  });
}

void EventDispatcher::removeEventListener(scene::Node* node, bool recursive)
{
  visitEventListenerVectors(0xfffffff, [&node, &recursive](auto& listener_vector){
    listener_vector.remove(node, recursive);
  });
}

void EventDispatcher::removeEventListener(int32_t listen_events)
{
  visitEventListenerVectors(listen_events, [](auto& listener_vector){
    listener_vector.clear();
  });
}

void EventDispatcher::dispatchEvent(Event& event)
{
  visitEventListenerVectors(static_cast<int32_t>(event.getType()), [&event](auto& listener_vector){

    auto& lower_fixed_listeners = listener_vector.getLowerFixedListeners();
    auto& upper_fixed_listeners = listener_vector.getUpperFixedListeners();
    auto& scene_graph_listeners = listener_vector.getSceneGraphListeners();

    for(auto& [fixed_priority, listener] : lower_fixed_listeners)
    {

    }

    for(auto& [node, listener] : scene_graph_listeners)
    {

    }

    for(auto& [fixed_priority, listener] : upper_fixed_listeners)
    {

    }

  });
}

void EventDispatcher::setEnabled(bool enabled)
{
  m_enabled = enabled;
}

bool EventDispatcher::isEnabled() const
{
  return m_enabled;
}

void EventDispatcher::visitEventListenerVectors(int32_t listen_events,
                                                const std::function<void(priv::EventListenerVector&)>& visitor)
{
  auto bitset = std::bitset<32>(listen_events);
  for(auto i = 0; i < bitset.size(); ++i)
  {
    if(!bitset.test(i))
      continue;

    auto flag = 1 << i;
    if(!m_event_to_listeners.contains(flag))
      m_event_to_listeners[flag] = std::make_unique<priv::EventListenerVector>(*this);

    visitor(*m_event_to_listeners[flag]);
  }
}

} // namespace egnim::event