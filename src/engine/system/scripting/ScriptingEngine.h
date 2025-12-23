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

        bool LoadModuleFromFile(const std::string& moduleName, const std::string& filePath);
        bool LoadModuleFromString(const std::string& moduleName, const std::string& virtualName, const std::string& code);

        bool Execute(const std::string& moduleName, const std::string& functionDecl);

        asIScriptEngine* GetAngelScriptEngine() const;

    private:
        static void MessageCallback(const asSMessageInfo* msg, void* param);
        static void ExceptionCallback(asIScriptContext* ctx, void* param);

        void RegisterAddons();

        std::unique_ptr<asIScriptEngine, AsEngineReleaser> m_engine;
    };
}

