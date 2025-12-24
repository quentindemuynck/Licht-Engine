#pragma once

#include <memory>
#include "ModuleInterface.h"
#include <Events/EventListener.h>

namespace licht
{
    class Renderer final : public licht::ModuleInterface
    {
    public:
        virtual void load_module(licht::Core& core);
        virtual void unload_module();

    private:
        std::unique_ptr<EventListener<>> m_updater;
    };
} // namespace licht
