#include "EventDispatcher.hpp"

void EventDispatcher::Dispatch(const IEvent& ev)
{
    for (auto& listener : m_listeners) {
        listener(ev);
    }
}

void EventDispatcher::AddListener(std::function<void(const IEvent&)> listener)
{
    m_listeners.push_back(listener);
}
