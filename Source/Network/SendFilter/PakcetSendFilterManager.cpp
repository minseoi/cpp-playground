/* Created by minseoi */

#include "PakcetSendFilterManager.h"

#include "Network/Packet/PacketBase.hpp"
#include "Filter/PacketSendFilterBase.h"

PacketSendFilterManager::PacketSendFilterManager()
{
    RegisterFilter<PacketSendFilterDoOnce>(PacketIndex::USE_ITEM_REQ, PacketIndex::USE_ITEM_ACK);
    RegisterFilter<PacketSendFilterCooldown>(PacketIndex::SET_TARGET_REQ, PacketIndex::SET_TARGET_ACK, 1000);
}

bool PacketSendFilterManager::CheckCanSend(const PacketBase &reqPacket) const
{
    if (const std::shared_ptr<PacketSendFilterBase>& Filter = GetFilter(reqPacket.GetIndex()))
    {
        return (*Filter)(false);
    }
    return true;
}

void PacketSendFilterManager::OnRecv(const PacketBase &ackPacket) const
{
    const std::optional<PacketIndex> reqIndex = GetReqFromAck(ackPacket.GetIndex());
    if (!reqIndex.has_value())
    {
        return;
    }

    if (const std::shared_ptr<PacketSendFilterBase>& Filter = GetFilter(reqIndex.value()))
    {
        (*Filter)(true);
    }
}

std::shared_ptr<PacketSendFilterBase> PacketSendFilterManager::GetFilter(const PacketIndex &_reqIndex) const
{
    if (const auto iter = m_filterMap.find(_reqIndex); iter != m_filterMap.end())
    {
        return iter->second;
    }
    return {};
}

std::optional<PacketIndex> PacketSendFilterManager::GetReqFromAck(PacketIndex _ackIndex) const
{
    if (const auto iter = m_packetPairMap.find(_ackIndex); iter != m_packetPairMap.end())
    {
        return iter->second;
    }
    return {};
}
