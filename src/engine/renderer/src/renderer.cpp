#include "Renderer.h"

#include <Core.h>
void licht::Renderer::load_module(licht::Core& core)
{
    m_updater = std::make_unique<EventListener<>>([] {
        spdlog::info("UPDATING");
    });
    core.get_update().add_listener(*m_updater);
}
void licht::Renderer::unload_module()
{
}