#ifndef GAMESPELL_EVENTS_CLOSE_WINDOW_EVENT_HPP
#define GAMESPELL_EVENTS_CLOSE_WINDOW_EVENT_HPP

#include "event.hh"

namespace gs {
class CloseWindowEvent : public Event {
public:
    CloseWindowEvent();
    ~CloseWindowEvent();

    virtual int getType() final { return 1; }
};
} // namespace gs

#endif // GAMESPELL_EVENTS_CLOSE_WINDOW_EVENT_HPP
