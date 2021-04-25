/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/events/event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::event {

Event::Event(Type type) :
  m_type(type),
  m_stopped(false)
{

}

Event::~Event() = default;

void Event::setStopped(bool stopped)
{
  m_stopped = stopped;
}

bool Event::isStopped() const
{
  return m_stopped;
}

Event::Type Event::getType() const
{
  return m_type;
}

} // namespace egnim::event