#include <gs/events/publisher.hh>

#include <algorithm>

namespace gs {
Publisher::Publisher() {
}

Publisher::~Publisher() {
}

void Publisher::attach(Subscriber& subscriber) {
    std::unique_lock<std::mutex> lock(mutex);

    attachedSubscribers.emplace_back(subscriber);
}

void Publisher::detach(Subscriber& subscriber) {
    std::unique_lock<std::mutex> lock(mutex);

    detachedSubscribers.emplace_back(subscriber);
}

void Publisher::publish(const Event& event) {
    std::unique_lock<std::mutex> lock(mutex);

    subscribers.erase(
        std::remove(subscribers.begin(), subscribers.end(), subscriber),
        subscribers.end());
}
} // namespace gs