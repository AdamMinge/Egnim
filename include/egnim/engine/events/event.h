#ifndef EVENT_H
#define EVENT_H

/* --------------------------------- Standard ------------------------------- */
#include <cstdint>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/core/object.h>
/* -------------------------------------------------------------------------- */

namespace egnim::events
{

  class EGNIM_UTILITY_API Event : public core::Object
  {
    EGNIM_CLASS(Event, core::Object)

  public:
    enum class Type;

  public:
    ~Event() override;

    void setStopped(bool stopped = true);
    [[nodiscard]] bool isStopped() const;

    [[nodiscard]] Type getType() const;

  protected:
    explicit Event(Type type);

  private:
    Type m_type;
    bool m_stopped;
  };

  enum class Event::Type : int32_t
  {
    Window    = 1 << 0,
    Keyboard  = 1 << 1,
    Mouse     = 1 << 2,
    Physics   = 1 << 3,

    Custom    = 1 << 31,
  };

} // namespace egnim::events

#endif //EVENT_H
