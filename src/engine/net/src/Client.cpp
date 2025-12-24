#include "../include/Client.h"

#include "Address.h"
#include "spdlog/spdlog.h"

#include <stdexcept>

namespace licht::net
{
    Client::Client()
    {
        // TODO: streamline channel count across hosts
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

    void Client::Connect(const std::string& ip, const uint16_t port)
    {
        ENetAddress address;
        enet_address_set_host(&address, ip.c_str());
        address.port = port;

        // TODO: wait x seconds to connect before giving up
        m_peer_ptr = enet_host_connect(m_client_ptr, &address, 2, 0);
        if (!m_peer_ptr)
        {
            throw std::runtime_error("Failed to create a new ENet Peer");
        }
    }

    void Client::Disconnect() const
    {
        // TODO: wait x seconds to attempt to disconnect and then forcefully disconnect
        enet_peer_disconnect(m_peer_ptr, 0);
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
                    spdlog::info("CLIENT - Connection to {} succeeded", addr.ToString());
                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE: {
                    printf("CLIENT - A packet of length %llu containing %p was received from %p on channel %u.\n",
                        event.packet->dataLength,
                        event.packet->data,
                        event.peer->data,
                        event.channelID);

                    /* Clean up the packet now that we're done using it. */
                    enet_packet_destroy (event.packet);
                    break;
                }

                case ENET_EVENT_TYPE_DISCONNECT: {
                    spdlog::info("CLIENT - Disconnected");
                    puts ("Disconnection succeeded.");
                    break;
                }

                default: {
                    spdlog::warn("CLIENT - Unhandled event type {}", event.peer->data);
                    break;
                }
            }
        }
    }
} // namespace licht::net