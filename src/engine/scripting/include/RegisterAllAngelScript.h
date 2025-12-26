#pragma once

#include "AngelScriptStubWriter.h"
#include <filesystem>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace licht::scripting
{

        // angel script functions
    inline void as_log_info(const std::string& msg)
    {
        spdlog::info(msg);
    }

    inline void as_log_warn(const std::string& msg)
    {
        spdlog::warn(msg);
    }

    inline void as_log_error(const std::string& msg)
    {
        spdlog::error(msg);
    }

    inline void register_all(asIScriptEngine& engine)
    {
        const auto outFile =
            std::filesystem::path(LICHT_PROJECT_ROOT) / "src" / "game" / "as.predefined";

        std::filesystem::create_directories(outFile.parent_path());

        spdlog::info("Writing stubs to: {}", outFile.string());

        AngelScriptStubWriter writer(outFile);

        writer.clear_and_begin();

        auto reg = licht::scripting::AngelScriptRegister(engine, writer);

        reg.add_a_global_function("void log_info(const string &in)", &as_log_info)
            .add_a_global_function("void log_warn(const string &in)", &as_log_warn)
            .add_a_global_function("void log_error(const string &in)", &as_log_error);

        writer.flush();
        spdlog::info("Wrote AngelScript stubs to {}", writer.path().string());
    }
}