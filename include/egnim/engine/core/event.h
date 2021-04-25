#ifndef EVENT_H
#define EVENT_H

namespace egnim::core
{

  class Event
  {
  public:
    explicit Event();
    virtual ~Event();

    void setStopped(bool stopped = true);
    [[nodiscard]] bool isStopped() const;

  private:
    bool m_stopped;
  };

} // namespace egnim::core

#endif //EVENT_H
