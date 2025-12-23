#include "server.h"

#include <stdexcept>

namespace licht::net
{
    Server::Server(const uint16_t port, const size_t max_clients, const size_t channels)
    {
        m_address.host = ENET_HOST_ANY;
        m_address.port = port;

        m_host_ptr = enet_host_create(&m_address, max_clients, channels, 0, 0);

        if (!m_host_ptr)
        {
            throw std::runtime_error("Failed to create a new ENet Host");
        }
    }

    Server::~Server()
    {
        enet_host_destroy(m_host_ptr);
        m_host_ptr = nullptr;
    }
} // namespace licht::net