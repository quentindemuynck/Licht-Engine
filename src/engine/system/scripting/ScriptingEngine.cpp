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
    }

    bool ScriptingEngine::LoadModuleFromFile(const std::string& moduleName, const std::string& filePath)
    {
        CScriptBuilder builder;
        int            r = builder.StartNewModule(m_engine.get(), moduleName.c_str());
        if (r < 0)
            return false;

        r = builder.AddSectionFromFile(filePath.c_str());
        if (r < 0)
        {
            spdlog::error("Failed to read script file: %s\n", filePath.c_str());
            return false;
        }

        r = builder.BuildModule();
        if (r < 0)
        {
            spdlog::error("BuildModule failed for %s\n", moduleName.c_str());
            return false;
        }

        return true;
    }

    bool ScriptingEngine::LoadModuleFromString(const std::string& moduleName,
                                               const std::string& virtualName,
                                               const std::string& code)
    {
        asIScriptModule* mod = m_engine->GetModule(moduleName.c_str(), asGM_ALWAYS_CREATE);
        if (!mod)
            return false;

        int r = mod->AddScriptSection(virtualName.c_str(), code.c_str(), (unsigned)code.size());
        if (r < 0)
            return false;

        r = mod->Build();
        if (r < 0)
            return false;

        return true;
    }

    bool ScriptingEngine::Execute(const std::string& moduleName, const std::string& functionDecl)
    {
        asIScriptModule* mod = m_engine->GetModule(moduleName.c_str());
        if (!mod)
        {
            spdlog::error("Module not found: %s\n", moduleName.c_str());
            return false;
        }

        asIScriptFunction* func = mod->GetFunctionByDecl(functionDecl.c_str());
        if (!func)
        {
            spdlog::error("Function not found: %s\n", functionDecl.c_str());
            return false;
        }

        asIScriptContext* ctx = m_engine->CreateContext();
        if (!ctx)
            return false;

        ctx->SetExceptionCallback(asFUNCTION(ScriptingEngine::ExceptionCallback), nullptr, asCALL_CDECL);

        int r = ctx->Prepare(func);
        if (r < 0)
        {
            ctx->Release();
            return false;
        }

        r = ctx->Execute();
        if (r != asEXECUTION_FINISHED)
        {
            if (r == asEXECUTION_EXCEPTION)
            {
                spdlog::error("Execution exception.\n");
            }
            else
            {
                spdlog::error("Execution failed code=%d\n", r);
            }
            ctx->Release();
            return false;
        }

        ctx->Release();
        return true;
    }

    asIScriptEngine* ScriptingEngine::GetAngelScriptEngine() const
    {
        return m_engine.get();
    }

    void ScriptingEngine::MessageCallback(const asSMessageInfo* msg, void* param)
    {
        const char* section = msg->section ? msg->section : "<unknown>";

        switch (msg->type)
        {
            case asMSGTYPE_ERROR:
                spdlog::error("{} ({}, {}): {}",
                              section,
                              msg->row,
                              msg->col,
                              msg->message);
                break;

            case asMSGTYPE_WARNING:
                spdlog::warn("{} ({}, {}): {}",
                             section,
                             msg->row,
                             msg->col,
                             msg->message);
                break;

            case asMSGTYPE_INFORMATION:
                spdlog::info("{} ({}, {}): {}",
                             section,
                             msg->row,
                             msg->col,
                             msg->message);
                break;

            default:
                break;
        }
    }

  void ScriptingEngine::ExceptionCallback(asIScriptContext* ctx, void*)
    {
        int         col = 0;
        const char* section = "<unknown>";
        int         line = ctx->GetExceptionLineNumber(&col, &section);

        const asIScriptFunction* fn = ctx->GetExceptionFunction();

        spdlog::error(
            "Script exception: {}\n"
            "{} ({}, {}): {}\n"
            "Function: {}\n"
            "Module: {}",
            ctx->GetExceptionString(),
            section ? section : "<unknown>",
            line,
            col,
            ctx->GetExceptionString(),
            fn ? fn->GetDeclaration() : "<unknown>",
            fn ? fn->GetModuleName() : "<unknown>");
    }



    void ScriptingEngine::RegisterAddons()
    {
        RegisterStdString(m_engine.get());
        RegisterScriptArray(m_engine.get(), true);
        RegisterScriptDictionary(m_engine.get());
    }
}