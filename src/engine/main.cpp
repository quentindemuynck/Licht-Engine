#include "SDL3/SDL_video.h"
#include "spdlog/spdlog.h"
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>

#include <Events/EventListener.h>
#include <Core.h>
#include "ScriptingEngine.h"

namespace
{
    SDL_Window* m_window;
    licht::Core core;
} // namespace

// angel script functions
void as_log_info(const std::string& msg)
{
    spdlog::info(msg);
}

void as_log_warn(const std::string& msg)
{
    spdlog::warn(msg);
}

void as_log_error(const std::string& msg)
{
    spdlog::error(msg);
}


SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv)
{
    m_window = SDL_CreateWindow("Editor", 1920, 1080, 0);
    spdlog::info("Hello");

    EventListener<> o_yea_i_hear{[](){
        spdlog::info("hello");
    }};

    core.get_update().add_listener(o_yea_i_hear);
    core.get_update().notify_listeners();

    licht::scripting::ScriptingEngine scriptingEngine;

    asIScriptEngine* engine = scriptingEngine.get_angel_script_engine();

    engine->RegisterGlobalFunction(
        "void log_info(const string &in)",
        asFUNCTION(as_log_info),
        asCALL_CDECL);

    engine->RegisterGlobalFunction(
        "void log_warn(const string &in)",
        asFUNCTION(as_log_warn),
        asCALL_CDECL);

    engine->RegisterGlobalFunction(
        "void log_error(const string &in)",
        asFUNCTION(as_log_error),
        asCALL_CDECL);


    scriptingEngine.load_module_from_file("Game", "game/main.as");
    scriptingEngine.execute("Game", "void main()");


    return SDL_AppResult::SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    return SDL_AppResult::SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    return SDL_AppResult::SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    // app.SDL_AppQuit(appstate, result);
}


