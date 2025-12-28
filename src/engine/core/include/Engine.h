#pragma once

#include "ModuleInterface.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <vector>

namespace licht::core
{
    template<typename... Modules>
    class Engine
    {
    public:
        // void add_update(ModuleInterface* module, std::function<void (*)(ModuleInterface*)> func);
        void update_loop();

        template<typename T>
        consteval T& get_module()
        {
            return std::get<T>(m_modules);
        }

    private:
        std::tuple<Modules...> m_modules;

        // std::vector<std::unique_ptr<ModuleInterface>>                        m_modules;
        // std::vector<std::pair<ModuleInterface*, void (*)(ModuleInterface*)>> m_update;
        // std::vector<std::pair<ModuleInterface*, void (*)(ModuleInterface*)>> m_fixed_update;
        // std::vector<std::pair<ModuleInterface*, void (*)(ModuleInterface*)>> m_;

        // template<typename T>
        // void add_module();
        // void subscribe_update()

        // Event<>& get_update();
        // Event<>& get_fixed_update();
        // Event<>& get_late_update();
        // Event<>& get_render();
    };

    template<typename T, typename = void>
    struct has_update : std::false_type
    {
    };

    template<typename T>
    struct has_update<T, std::void_t<decltype(std::declval<T>().update())>> : std::true_type
    {
    };

    template<typename T, typename = void>
    struct has_fixed_update : std::false_type
    {
    };

    template<typename T>
    struct has_fixed_update<T, std::void_t<decltype(std::declval<T>().fixed_update())>> : std::true_type
    {
    };

    template<typename... Modules>
    void Engine<Modules...>::update_loop()
    {
        std::apply([]<typename... T>(T&... modules) {
            ([&modules]() {
                if constexpr (has_update<T>::value)
                {
                    modules.update();
                }
            }(),
             ...);
        },
                   m_modules);

        

        std::apply([]<typename... T>(T&... modules) {
            ([&modules]() {
                if constexpr (has_fixed_update<T>::value)
                {
                    modules.fixed_update();
                }
            }(),
             ...);
        },
                   m_modules);
    }
} // namespace licht::core
