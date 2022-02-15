#ifndef GAMESPELL_EVENTS_PUBLISHER_HH
#define GAMESPELL_EVENTS_PUBLISHER_HH

#include "subscriber.hh"

#include <functional>
#include <mutex>
#include <queue>
#include <vector>

namespace gs {
class Publisher {
public:
    Publisher();
    ~Publisher();

    void attach(Subscriber& subscriber);
    void detach(Subscriber& subscriber);

    void publish(const Event& event);

private:
    std::queue<Event>                               events;
    std::vector<std::reference_wrapper<Subscriber>> attachedSubscribers;
    std::vector<std::reference_wrapper<Subscriber>> detachedSubscribers;
    std::mutex                                      mutex;
};
} // namespace gs

#endif // GAMESPELL_EVENTS_PUBLISHER_HH
