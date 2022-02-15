#ifndef GAMESPELL_EVENTS_EVENT_HH
#define GAMESPELL_EVENTS_EVENT_HH

namespace gs {
class Event {
public:
    virtual int getType() const = 0;
};
} // namespace gs

#endif // GAMESPELL_EVENTS_EVENT_HH
