#include "../include/net.h"
#include <enet.h>
#include <spdlog/spdlog.h>

namespace licht::net
{
    NetModule::NetModule()
    {
        spdlog::info("Loading network module");

        if (enet_initialize () != 0)
        {
            spdlog::error("Failed to initialize enet: {}", EXIT_FAILURE);
            return;
        }

        m_initialized = true;
    }

    NetModule::~NetModule()
    {
        spdlog::info("Unloading network module");
        enet_deinitialize();
    }
}