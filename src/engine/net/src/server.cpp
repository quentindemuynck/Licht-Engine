#include "server.h"

#include "Address.h"
#include "spdlog/spdlog.h"

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

    void Server::HandlePackets() const
    {
        ENetEvent event{};
        while(enet_host_service(m_host_ptr, &event, 0) > 0)
        {
            switch (event.type)
            {
                case ENET_EVENT_TYPE_CONNECT: {
                    Address addr{event.peer->address};
                    spdlog::info("SERVER - A new client connected from %x:%u.\n",
                            addr.ToString(),
                            addr.Port());

                    // Ability to store some client information
                    // event.peer->data = "Client information";

                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE: {
                    printf("SERVER - A packet of length %llu containing %p was received from %p on channel %u.\n",
                        event.packet->dataLength,
                        event.packet->data,
                        event.peer->data,
                        event.channelID);

                    /* Clean up the packet now that we're done using it. */
                    enet_packet_destroy (event.packet);
                    break;
                }

                case ENET_EVENT_TYPE_DISCONNECT: {
                    spdlog::info("SERVER - %s disconnected.\n", event.peer->data);

                    // Reset client information
                    event.peer->data = nullptr;
                    break;
                }

                default: {
                    spdlog::warn("SERVER - Unhandled event type {}", event.peer->data);
                    break;
                }
            }
        }
    }
} // namespace licht::net