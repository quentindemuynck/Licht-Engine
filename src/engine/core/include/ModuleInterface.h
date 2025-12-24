#pragma once

#include "DisableCopyMove.h"

namespace licht
{
    class Core;
    class ModuleInterface
    {
    public:
        ModuleInterface() = default;
        DISABLE_COPY(ModuleInterface);
        DISABLE_MOVE(ModuleInterface);
        virtual ~ModuleInterface() = default;

        virtual void load_module(licht::Core& core) = 0;
        virtual void unload_module() = 0;
    };
} // namespace licht
