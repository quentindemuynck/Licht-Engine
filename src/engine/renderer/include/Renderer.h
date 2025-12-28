#pragma once

#include <memory>
#include "ModuleInterface.h"

#include <Engine.h>
#include <Events/EventListener.h>

namespace licht
{
    class Renderer final : public licht::ModuleInterface
    {
    public:
        void load_module() override;
        void unload_module() override;

        void update();
        void fixed_update();
    };
} // namespace licht
