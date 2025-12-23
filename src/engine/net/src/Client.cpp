#include "../include/Client.h"

#include <stdexcept>

namespace licht::net
{
    Client::Client()
    {
        m_client_ptr = enet_host_create (nullptr, 1, 2, 0, 0);

        if (!m_client_ptr)
        {
            throw std::runtime_error("Failed to create a new ENet Client");
        }
    }

    Client::~Client()
    {
        enet_host_destroy(m_client_ptr);
    }
}