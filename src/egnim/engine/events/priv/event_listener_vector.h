#ifndef EVENT_LISTENER_VECTOR_H
#define EVENT_LISTENER_VECTOR_H

/* --------------------------------- Standard ------------------------------- */
#include <set>
#include <map>
#include <list>
#include <utility>
#include <cstdint>
/* -------------------------------------------------------------------------- */

namespace egnim
{
  namespace scene { class Node; }
  namespace event { class EventListener; class EventDispatcher; }
}

namespace egnim::event::priv
{

  struct FixedListenerComparator
  {
    [[nodiscard]] bool operator()(const std::pair<int, EventListener*>& first_key,
                                  const std::pair<int, EventListener*>& second_key) const;
  };

  class EventListenerVector
  {
  public:
    using FixedListeners = std::set<std::pair<int, EventListener*>, FixedListenerComparator>;
    using SceneGraphListeners = std::list<std::pair<scene::Node*, EventListener*>>;

  public:
    explicit EventListenerVector(EventDispatcher& event_dispatcher);
    ~EventListenerVector();

    void append(EventListener* event_listener, scene::Node* node);
    void append(EventListener* event_listener, int fixed_priority);

    void remove(EventListener* event_listener);
    void remove(scene::Node* node, bool recursive = false);

    [[nodiscard]] const FixedListeners& getLowerFixedListeners() const;
    [[nodiscard]] const FixedListeners& getUpperFixedListeners() const;
    [[nodiscard]] const SceneGraphListeners& getSceneGraphListeners() const;

    [[nodiscard]] size_t size() const;
    [[nodiscard]] bool empty() const;

    void clear();
    void sort();

  private:
    [[nodiscard]] std::map<scene::Node*, int> getSceneGraphNodeDepth() const;

  private:
    EventDispatcher& m_event_dispatcher;
    FixedListeners m_lower_fixed_listeners;
    FixedListeners m_upper_fixed_listeners;
    SceneGraphListeners m_scene_graph_listeners;
  };

} // namespace egnim::event

#endif //EVENT_LISTENER_VECTOR_H
