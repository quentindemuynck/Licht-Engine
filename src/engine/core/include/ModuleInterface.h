#pragma once

namespace licht
{
    class ModuleInterface
    {
    public:
        ModuleInterface() = default;
        virtual ~ModuleInterface() = default;
        ModuleInterface(const ModuleInterface&) = delete;
        ModuleInterface& operator=(const ModuleInterface&) = delete;
        ModuleInterface(ModuleInterface&&) = delete;
        ModuleInterface& operator=(ModuleInterface&&) = delete;

        virtual void load_module() = 0;
        virtual void unload_module() = 0;
    };
} // namespace licht
