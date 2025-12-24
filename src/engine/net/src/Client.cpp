#include "../include/Client.h"

#include "Address.h"
#include "spdlog/spdlog.h"

#include <stdexcept>

namespace licht::net
{
    Client::Client()
    {
        m_client_ptr = enet_host_create(nullptr, 1, 2, 0, 0);

        if (!m_client_ptr)
        {
            throw std::runtime_error("Failed to create a new ENet Client");
        }
    }

    Client::~Client()
    {
        enet_host_destroy(m_client_ptr);
    }

    void Client::HandlePackets() const
    {
        ENetEvent event{};
        while(enet_host_service(m_client_ptr, &event, 0) > 0)
        {
            switch (event.type)
            {
                case ENET_EVENT_TYPE_CONNECT: {
                    Address addr{event.peer->address};
                    spdlog::info("A new client connected from %x:%u.\n",
                            addr.ToString(),
                            addr.Port());

                    // Ability to store some client information
                    // event.peer->data = "Client information";

                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE: {
                    printf("A packet of length %llu containing %p was received from %p on channel %u.\n",
                        event.packet->dataLength,
                        event.packet->data,
                        event.peer->data,
                        event.channelID);

                    /* Clean up the packet now that we're done using it. */
                    enet_packet_destroy (event.packet);
                    break;
                }

                case ENET_EVENT_TYPE_DISCONNECT: {
                    spdlog::info("%s disconnected.\n", event.peer->data);

                    // Reset client information
                    event.peer->data = nullptr;
                    break;
                }

                default: {
                    spdlog::warn("Unhandled event type {}", event.peer->data);
                    break;
                }
            }
        }
    }
} // namespace licht::net