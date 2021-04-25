#ifndef EVENT_H
#define EVENT_H

/* --------------------------------- Standard ------------------------------- */
#include <cstdint>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/core/object.h>
/* -------------------------------------------------------------------------- */

namespace egnim::event
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
    Keyboard  = 1 << 0,
    Mouse     = 1 << 1,

    Custom    = 1 << 31,
  };

} // namespace egnim::event

#endif //EVENT_H
