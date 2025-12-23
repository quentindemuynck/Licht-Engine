#pragma once

#include <angelscript.h>
#include <string>
#include <memory>

namespace licht::system::scripting
{
    struct AsEngineReleaser
    {
        void operator()(asIScriptEngine* engine) const noexcept
        {
            if (engine)
            {
                engine->ShutDownAndRelease();
            }
        }
    };

    class ScriptingEngine final
    {
    public:
        ScriptingEngine();
        ~ScriptingEngine() = default;

        ScriptingEngine(const ScriptingEngine&) = delete;
        ScriptingEngine& operator=(const ScriptingEngine&) = delete;

        bool load_module_from_file(const std::string& moduleName, const std::string& filePath);
        bool load_module_from_string(const std::string& moduleName, const std::string& virtualName, const std::string& code);

        bool execute(const std::string& moduleName, const std::string& functionDecl);

        asIScriptEngine* get_angel_script_engine() const;

    private:
        static void message_callback(const asSMessageInfo* msg, void* param);
        static void exception_callback(asIScriptContext* ctx, void* param);

        void register_addons();

        std::unique_ptr<asIScriptEngine, AsEngineReleaser> m_engine;
    };
}

