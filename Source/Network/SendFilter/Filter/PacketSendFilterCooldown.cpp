/* Created by minseoi */

#include "PacketSendFilterCooldown.h"

#include "Log/LogDefinition.h"

bool PacketSendFilterCooldown::operator()(const bool isRecv)
{
    if (!isRecv)
    {
        const auto now = std::chrono::steady_clock::now();
        const auto elpasedTime = now - m_lastSendTime;
        if (elpasedTime < m_cooldown)
        {
            LOG_I("Block");
            return false;
        }

        m_lastSendTime = now;
        LOG_I("Allow");
        return true;
    }

    return true;
}
