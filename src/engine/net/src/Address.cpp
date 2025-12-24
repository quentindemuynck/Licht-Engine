#include "../include/Address.h"

namespace licht::net
{

    Address::Address(const ENetAddress& addr) noexcept
            : address(addr)
    {

    }

    std::string Address::ToString() const noexcept
    {
        char buffer[ENET_ADDRESS_MAX_HOSTNAME];
        enet_address_get_host_ip(&address, buffer, sizeof(buffer));
        return std::string{buffer};
    }

    uint16_t Address::Port() const noexcept
    {
        return address.port;
    }
} // namespace licht::net