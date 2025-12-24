#pragma once
#include "enet.h"

namespace licht::net
{
    class Client final
    {
    public:
        Client();
        ~Client();

        Client(const Client&) = delete;
        Client(Client&&) = delete;
        Client& operator=(const Client&) = delete;
        Client& operator=(Client&&) = delete;
    private:
        void HandlePackets() const;

        ENetHost* m_client_ptr{ nullptr };
    };
}