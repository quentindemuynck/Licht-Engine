#pragma once
#include "enet.h"

#include <string>

namespace licht::net
{
    class Address final
    {
    public:
        explicit Address(const ENetAddress& addr) noexcept;
        ~Address() = default;

        [[nodiscard]] std::string ToString() const noexcept;
        [[nodiscard]] uint16_t Port() const noexcept;

        Address(const Address&) = delete;
        Address(Address&&) = delete;
        Address& operator=(const Address&) = delete;
        Address& operator=(Address&&) = delete;
    private:
        static constexpr size_t ENET_ADDRESS_MAX_HOSTNAME = 20;

        ENetAddress address;
    };
} // namespace licht::net