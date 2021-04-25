/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

Event::Event() :
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

} // namespace egnim::core