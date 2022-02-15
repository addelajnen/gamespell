#ifndef GAMESPELL_EVENTS_SUBSCRIBER_HH
#define GAMESPELL_EVENTS_SUBSCRIBER_HH

#include "event.hh"

namespace gs {
class Subscriber {
public:
    virtual void onEvent(const Event& event) = 0;
};
} // namespace gs

#endif // GAMESPELL_EVENTS_SUBSCRIBER_HH
