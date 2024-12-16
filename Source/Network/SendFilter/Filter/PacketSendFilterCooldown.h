/* Created by minseoi */

#pragma once
#include <chrono>

#include "PacketSendFilterBase.h"


class PacketSendFilterCooldown final : public PacketSendFilterBase
{
private:
    std::chrono::steady_clock::time_point m_lastSendTime {};
    const std::chrono::milliseconds m_cooldown {};

public:
    explicit PacketSendFilterCooldown(const uint _cooldown) :
        PacketSendFilterBase(),
        m_cooldown(std::chrono::milliseconds(_cooldown))
    {
    }

    bool operator()(const bool isRecv) override;
};
