#pragma once
#include "enet.h"

namespace licht::net
{
    class Server final
    {
    public:
        explicit Server(uint16_t port, size_t max_clients, size_t channels);
        ~Server();

        Server(const Server&) = delete;
        Server(Server&&) = delete;
        Server& operator=(const Server&) = delete;
        Server& operator=(Server&&) = delete;

    private:
        void HandlePackets() const;

        ENetAddress m_address{};
        ENetHost* m_host_ptr{ nullptr };
    };
}
