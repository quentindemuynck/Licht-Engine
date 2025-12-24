#include "SDL3/SDL_video.h"
#include "spdlog/spdlog.h"
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>

#include <Core.h>
#include <Renderer.h>

namespace
{
    licht::Core core;
} // namespace

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv)
{
    core.init();
    core.add_module<licht::Renderer>();

    core.start();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    core.update();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    // app.SDL_AppQuit(appstate, result);
}
