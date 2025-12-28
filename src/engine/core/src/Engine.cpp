#include "Engine.h"
#include "CoreInternal.h"

// namespace
// {
//     // licht::Event<> update_event;
//     // licht::Event<> fixed_update;
//     // licht::Event<> late_update;
//     // licht::Event<> render;
//
//     SDL_Window* window;
// } // namespace
//
// void licht::core::internal::init()
// {
//     window = SDL_CreateWindow("Licht Engine", 1440, 810, 0);
// }
//
// void licht::core::internal::start()
// {
//     // for (const auto& module : modules)
//     // {
//     //     module->load_module();
//     // }
// }
// void licht::core::internal::update()
// {
//     // update_event.notify_listeners();
//     // fixed_update.notify_listeners();
//     // render.notify_listeners();
// }
// void licht::core::internal::event()
// {
// }
// void licht::core::internal::quit()
// {
// }
//
// void licht::core::Engine::add_update(ModuleInterface* module, std::function<void (*)(ModuleInterface*)> yes)
// {
//     m_update.emplace_back(module, yes);
// }
// void licht::core::Engine::update_loop()
// {
//     for (auto& [module, func] : m_update)
//     {
//         func(module);
//     }
// }