#pragma once
#include "enet.h"

#include <string>

namespace licht::net
{
    class Client final
    {
    public:
        Client();
        ~Client();

        void Connect(const std::string& ip, uint16_t port);
        void Disconnect() const;

        Client(const Client&) = delete;
        Client(Client&&) = delete;
        Client& operator=(const Client&) = delete;
        Client& operator=(Client&&) = delete;
    private:
        void HandlePackets() const;

        ENetHost* m_client_ptr{ nullptr };
        ENetPeer* m_peer_ptr{ nullptr };
    };
}