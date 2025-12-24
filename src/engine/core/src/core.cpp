#include "Core.h"

void licht::Core::init()
{
    m_window = SDL_CreateWindow("Licht Engine", 1440, 810, 0);
}

void licht::Core::start()
{
    for (auto& module : m_modules)
    {
        module->load_module(*this);
    }
}
void licht::Core::update()
{
    m_update.notify_listeners();
    m_fixed_update.notify_listeners();
    m_render.notify_listeners();
}
void licht::Core::event()
{
}
void licht::Core::quit()
{
}

licht::Event<>& licht::Core::get_update()
{
    return m_update;
};
licht::Event<>& licht::Core::get_fixed_update()
{
    return m_fixed_update;
};
licht::Event<>& licht::Core::get_late_update()
{
    return m_late_update;
};
licht::Event<>& licht::Core::get_render()
{
    return m_render;
};
