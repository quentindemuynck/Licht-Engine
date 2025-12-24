#pragma once
#include <vector>

namespace licht
{
    template<typename... Args>
    class EventListener;

    template<typename... Args>
    class Event final
    {
    public:
        Event() = default;
        ~Event();

        Event(const Event& other) = delete;
        Event& operator=(const Event& other) = delete;

        Event(Event&& other) noexcept;
        Event& operator=(Event&& other) noexcept;

        void add_listener(EventListener<Args...>& listener);
        void remove_listener(EventListener<Args...>& listener);

        void notify_listeners(Args... args);

    private:
        std::vector<EventListener<Args...>*> m_function_pointers;
    };
} // namespace licht

#include "EventListener.h"

template<typename... Args>
licht::Event<Args...>::~Event()
{
    for (EventListener<Args...>* functions : m_function_pointers)
    {
        functions->remove_from_event_internal();
    }
}

template<typename... Args>
licht::Event<Args...>::Event(Event&& other) noexcept
    : m_function_pointers(std::move(other.m_function_pointers))
{
    other.m_function_pointers.clear();

    for (EventListener<Args...>* function : m_function_pointers)
    {
        function->set_event_internal(this);
    }
}

template<typename... Args>
licht::Event<Args...>& licht::Event<Args...>::operator=(Event&& other) noexcept
{
    if (this != &other)
    {
        m_function_pointers = std::move(other.m_function_pointers);
        other.m_function_pointers.clear();
        for (EventListener<Args...>* function : m_function_pointers)
        {
            function->set_event_internal(this);
        }
    }

    return *this;
}

template<typename... Args>
void licht::Event<Args...>::add_listener(EventListener<Args...>& listener)
{
    listener.set_event_internal(this);
    m_function_pointers.push_back(&listener);
}

template<typename... Args>
void licht::Event<Args...>::remove_listener(EventListener<Args...>& listener)
{
    listener.remove_from_event_internal();
    std::erase(m_function_pointers, &listener);
}

template<typename... Args>
void licht::Event<Args...>::notify_listeners(Args... args)
{
    for (EventListener<Args...>* function : m_function_pointers)
    {
        function->call_function(std::forward<Args>(args)...);
    }
}
