#pragma once

namespace licht::net
{
    class NetModule final
    {
    public:
        NetModule();
        ~NetModule();

        NetModule(const NetModule&) = delete;
        NetModule(NetModule&&) = delete;
        NetModule& operator=(const NetModule&) = delete;
        NetModule& operator=(NetModule&&) = delete;

    private:
        bool m_initialized{ false };
    };
}
