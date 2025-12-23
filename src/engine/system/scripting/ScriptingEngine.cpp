#include "ScriptingEngine.h"

#include <cassert>
#include <cstdio>

// Add-ons
#include <scriptstdstring.h>
#include <scriptarray.h>
#include <scriptdictionary.h>
#include <scriptbuilder.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace licht::system::scripting
{
    ScriptingEngine::ScriptingEngine()
        : m_engine(asCreateScriptEngine())
    {
        if (!m_engine.get())
        {
            spdlog::error("failed to create AngelScript engine!");
        }

        int r = m_engine->SetMessageCallback(asFUNCTION(ScriptingEngine::MessageCallback), nullptr, asCALL_CDECL);
        m_engine->SetEngineProperty(asEP_ALLOW_UNSAFE_REFERENCES, 1);

        RegisterAddons();
        RegisterAPI();
    }

    bool ScriptingEngine::LoadModuleFromFile(const std::string& moduleName, const std::string& filePath)
    {
        return false;
    }

    bool ScriptingEngine::LoadModuleFromString(const std::string& moduleName,
                                               const std::string& virtualName,
                                               const std::string& code)
    {
        return false;
    }

    bool ScriptingEngine::Execute(const std::string& moduleName, const std::string& functionDecl)
    {
        return false;
    }

    asIScriptEngine* ScriptingEngine::GetAngelScriptEngine() const
    {
        return nullptr;
    }

    void ScriptingEngine::MessageCallback(const asSMessageInfo* msg, void* param)
    {
    }

    void ScriptingEngine::ExceptionCallback(asIScriptContext* ctx, void* param)
    {
    }

    void ScriptingEngine::Print(const std::string& s)
    {
    }

    void ScriptingEngine::RegisterAddons()
    {
        RegisterStdString(m_engine.get());
        RegisterScriptArray(m_engine.get(), true);
        RegisterScriptDictionary(m_engine.get());
    }

    void ScriptingEngine::RegisterAPI()
    {
    }
}