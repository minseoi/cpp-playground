#include <iostream>
#include <thread>

#include "Log/LogDefinition.h"


enum PacketIndex : unsigned int
{
    USE_ITEM_REQ = 1000,
    USE_ITEM_ACK = 1001,
    SET_TARGET_REQ = 1010,
    SET_TARGET_ACK = 1011
};

class PacketBase
{
    PacketIndex m_index {};

public:
    explicit PacketBase(PacketIndex _packetIndex) :
        m_index(_packetIndex)
    {
    }
    explicit PacketBase() = delete;
    virtual ~PacketBase() = default;
    [[nodiscard]] PacketIndex GetIndex() const
    {
        return m_index;
    }
};

// ****************************************************************************** //

class PacketSendFilterBase
{
public:
    explicit PacketSendFilterBase() = default;
    virtual ~PacketSendFilterBase() = default;

    virtual bool operator()(bool _isRecv) = 0;
};

class PacketSendFilterDoOnce final : public PacketSendFilterBase
{
private:
    bool m_allow {};

public:
    explicit PacketSendFilterDoOnce() :
        PacketSendFilterBase()
    {
    }

    bool operator() (bool _isRecv) override
    {
        if (!_isRecv)
        {
            if (m_allow)
            {
                LOG_I("Block");
                return false;
            }

            m_allow = true;
            LOG_I("Allow");
            return true;
        }

        LOG_I("Free");
        m_allow = false;
        return true;
    }
};

class PacketSendFilterCooldown final : public PacketSendFilterBase
{
private:
    std::chrono::steady_clock::time_point m_lastSendTime {};
    const std::chrono::milliseconds m_cooldown {};

public:
    explicit PacketSendFilterCooldown(const std::chrono::milliseconds _cooldown) :
        PacketSendFilterBase(),
        m_cooldown(_cooldown)
    {
    }

    bool operator()(const bool _isRecv) override
    {
        if (!_isRecv)
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
};

class PacketSendFilterManager
{
private:
    std::unordered_map<PacketIndex, std::shared_ptr<PacketSendFilterBase>> m_filterMap {};
    std::unordered_map<PacketIndex, PacketIndex> m_packetPairMap {};

public:
    explicit PacketSendFilterManager()
    {
        RegisterFilter<PacketSendFilterDoOnce>(PacketIndex::USE_ITEM_REQ, PacketIndex::USE_ITEM_ACK);
        RegisterFilter<PacketSendFilterCooldown>(PacketIndex::SET_TARGET_REQ, PacketIndex::SET_TARGET_ACK, 1000);
    }

    [[nodiscard]] bool CheckCanSend(const PacketBase& _reqPacket) const
    {
        if (const std::shared_ptr<PacketSendFilterBase>& Filter = GetFilter(_reqPacket.GetIndex()))
        {
            return (*Filter)(false);
        }
        return true;
    }

    void OnRecv(const PacketBase& _ackPacket) const
    {
        const std::optional<PacketIndex> reqIndex = GetReqFromAck(_ackPacket.GetIndex());
        if (!reqIndex.has_value())
        {
            return;
        }

        if (const std::shared_ptr<PacketSendFilterBase>& Filter = GetFilter(reqIndex.value()))
        {
            (*Filter)(true);
        }
    }

private:
    [[nodiscard]] std::shared_ptr<PacketSendFilterBase> GetFilter(const PacketIndex& _reqIndex) const
    {
        if (const auto iter = m_filterMap.find(_reqIndex); iter != m_filterMap.end())
        {
            return iter->second;
        }
        return {};
    }

    [[nodiscard]] std::optional<PacketIndex> GetReqFromAck(PacketIndex _ackIndex) const
    {
        if (const auto iter = m_packetPairMap.find(_ackIndex); iter != m_packetPairMap.end())
        {
            return iter->second;
        }
        return {};
    }

    template<typename FilterType, typename... Args>
    inline void RegisterFilter(PacketIndex _reqIndex, PacketIndex _ackIndex, Args&&... _args)
    {
        m_filterMap.emplace(_reqIndex, std::make_shared<FilterType>(std::forward<Args>(_args)...));
        m_packetPairMap.emplace(_ackIndex, _reqIndex);
    }

};

// ****************************************************************************** //

PacketSendFilterManager SendFilerManager;

void Send(const std::shared_ptr<PacketBase>& _packet)
{
    if (_packet == nullptr)
    {
        return;
    }
    LOG_D("%d", _packet->GetIndex());
}

void TrySend(const std::shared_ptr<PacketBase>& _packet)
{
    if (_packet == nullptr)
    {
        return;
    }
    LOG_D("%d", _packet->GetIndex());
    if (SendFilerManager.CheckCanSend(*_packet))
    {
        Send(_packet);
    }
}

void OnRecvPacket(const std::shared_ptr<PacketBase>& _packet)
{
    if (_packet == nullptr)
    {
        return;
    }
    LOG_D("%d", _packet->GetIndex());
    SendFilerManager.OnRecv(*_packet);
}

int main()
{
    auto packet = std::make_shared<PacketBase>(PacketIndex::USE_ITEM_REQ);
    TrySend(packet);
    TrySend(packet);

    return 0;
}