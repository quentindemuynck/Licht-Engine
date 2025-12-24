#pragma once

#include "ModuleInterface.h"
#include "Events/Event.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <vector>
#include <SDL3/SDL_init.h>

namespace licht
{
    class Core
    {
    public:
        // TODO: Need TO MAKE FRIEND
        void init();

        void start();
        void update();
        void event();
        void quit();

        template<typename T>
        void add_module();

        Event<>& get_update();
        Event<>& get_fixed_update();
        Event<>& get_late_update();
        Event<>& get_render();

    private:
        std::vector<std::unique_ptr<ModuleInterface>> m_modules;

        Event<> m_update;
        Event<> m_fixed_update;
        Event<> m_late_update;
        Event<> m_render;

        SDL_Window* m_window;
    };

    template<typename T>
    void Core::add_module()
    {
        m_modules.push_back(std::make_unique<T>());
    }

} // namespace licht
