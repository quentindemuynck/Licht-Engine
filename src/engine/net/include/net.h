#pragma once

namespace licht::net
{
    class net final
    {
    public:
        net() = default;
        ~net() = default;

        net(const net&) = delete;
        net(net&&) = delete;
        net& operator=(const net&) = delete;
        net& operator=(net&&) = delete;

    private:
        // TODO: members
    };
}
