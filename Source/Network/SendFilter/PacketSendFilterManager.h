/* Created by minseoi */

#pragma once
#include <unordered_map>

#include "Network/NetworkDefinition.h"
#include "Network/Packet/PacketDefinition.h"


class PacketBase;
class PacketSendFilterBase;

class PacketSendFilterManager
{
private:
    std::unordered_map<PacketIndex, std::shared_ptr<PacketSendFilterBase>> m_filterMap {};
    std::unordered_map<PacketIndex, PacketIndex> m_packetPairMap {};

public:
    explicit PacketSendFilterManager();

    [[nodiscard]] bool CheckCanSend(const PacketBase& reqPacket) const;
    void OnRecv(const PacketBase& ackPacket) const;

private:
    [[nodiscard]] std::shared_ptr<PacketSendFilterBase> GetFilter(const PacketIndex& _reqIndex) const;
    [[nodiscard]] std::optional<PacketIndex> GetReqFromAck(PacketIndex _ackIndex) const;

    template<typename FilterType, typename... Args>
    void RegisterFilter(PacketIndex _reqIndex, PacketIndex _ackIndex, Args&&... _args);
};

template<typename FilterType, typename ... Args>
void PacketSendFilterManager::RegisterFilter(PacketIndex _reqIndex, PacketIndex _ackIndex, Args &&..._args)
{
    m_filterMap.emplace(_reqIndex, std::make_shared<FilterType>(std::forward<Args>(_args)...));
    m_packetPairMap.emplace(_ackIndex, _reqIndex);
}
