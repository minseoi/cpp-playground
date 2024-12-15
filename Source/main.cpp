#include <iostream>
#include "Log/LogDefinition.h"


enum class PacketIndex : unsigned int
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

    virtual void Send_Impl() {}; //실제 패킷 전송 대신 REQ에서 각자 ACK를 받도록 구현
};

void OnRecvPacket(const std::shared_ptr<PacketBase>& _packet);

class PACKET_USE_ITEM_ACK final : public PacketBase
{
public:
    PACKET_USE_ITEM_ACK() :
    PacketBase(PacketIndex::USE_ITEM_ACK)
    {
    }
};
class PACKET_USE_ITEM_REQ final : public PacketBase
{
public:
    PACKET_USE_ITEM_REQ() :
    PacketBase(PacketIndex::USE_ITEM_REQ)
    {
    }

    void Send_Impl() override
    {
        //OnRecvPacket(std::make_shared<PACKET_USE_ITEM_ACK>());
    }
};

// ****************************************************************************** //

class PacketSendFilterBase : std::enable_shared_from_this<PacketSendFilterBase>
{
public:
    explicit PacketSendFilterBase() = default;
    virtual ~PacketSendFilterBase() = default;

    virtual bool operator()(bool _isRecv) = 0;
};

class PacketSendFilter_DoOnce final : public PacketSendFilterBase
{
private:
    bool m_allow {};

public:
    explicit PacketSendFilter_DoOnce() :
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

class PacketSendFilter_Cooldown final : public PacketSendFilterBase
{
private:
    std::time_t m_lastSendTime {};
    const std::time_t m_cooldown {};

public:
    explicit PacketSendFilter_Cooldown(std::time_t _cooldown) :
        PacketSendFilterBase(),
        m_cooldown(_cooldown)
    {
    }

    bool operator()(bool _isRecv) override
    {
        if (!_isRecv)
        {
            const std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            const std::time_t elpasedTime = now - m_lastSendTime;
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

#define REGISTER_SEND_FILTER(REQ_INDEX, ACK_INDEX, FILTER_TYPE, ...) \
ADD_PACKET_PAIR_MAP(REQ_INDEX, ACK_INDEX) \
ADD_FILTER(REQ_INDEX, FILTER_TYPE, __VA_ARGS__)

#define ADD_PACKET_PAIR_MAP(REQ_INDEX, ACK_INDEX) \
m_packetPairMap.emplace(ACK_INDEX, REQ_INDEX);

#define ADD_FILTER(REQ_INDEX, FILTER_TYPE, ...) \
m_filterMap.emplace(REQ_INDEX, std::make_shared<FILTER_TYPE>(__VA_ARGS__))

class PacketSendFilterManager
{
private:
    std::unordered_map<PacketIndex, std::shared_ptr<PacketSendFilterBase>> m_filterMap {};
    std::unordered_map<PacketIndex, PacketIndex> m_packetPairMap {};

public:
    explicit PacketSendFilterManager()
    {
        REGISTER_SEND_FILTER(PacketIndex::USE_ITEM_REQ, PacketIndex::USE_ITEM_ACK, PacketSendFilter_DoOnce);
        REGISTER_SEND_FILTER(PacketIndex::SET_TARGET_REQ, PacketIndex::SET_TARGET_ACK, PacketSendFilter_Cooldown, 1.0f);
    }

    bool CheckCanSend(const std::shared_ptr<PacketBase>& _reqPacket)
    {
        if (_reqPacket == nullptr)
        {
            return false;
        }

        if (const std::shared_ptr<PacketSendFilterBase>& Filter = GetFilter(_reqPacket))
        {
            return (*Filter)(false);
        }
        return true;
    }

    void OnRecv(const std::shared_ptr<PacketBase>& _ackPacket)
    {
        if (_ackPacket == nullptr)
        {
            return;
        }

        const std::optional<PacketIndex> reqIndex = GetReqFromAck(_ackPacket->GetIndex());
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
    std::shared_ptr<PacketSendFilterBase> GetFilter(const std::shared_ptr<PacketBase>& _reqPacket)
    {
        if (_reqPacket == nullptr)
        {
            return {};
        }

        return GetFilter(_reqPacket->GetIndex());
    }

    std::shared_ptr<PacketSendFilterBase> GetFilter(const PacketIndex& _reqIndex)
    {
        const auto iter = m_filterMap.find(_reqIndex);
        if (iter == m_filterMap.end())
        {
            return {};
        }

        return iter->second;
    }

    std::optional<PacketIndex> GetReqFromAck(PacketIndex _ackIndex)
    {
        const auto iter = m_packetPairMap.find(_ackIndex);
        if (iter == m_packetPairMap.end())
        {
            return {};
        }

        return iter->second;
    }
};

// ****************************************************************************** //

PacketSendFilterManager SendFilerManager;

void Send(const std::shared_ptr<PacketBase>& _packet)
{
    if (_packet)
    {
        LOG_D("%d", _packet->GetIndex());
        _packet->Send_Impl();
    }
}

void TrySend(const std::shared_ptr<PacketBase>& _packet)
{
    LOG_D("%d", _packet->GetIndex());
    if (SendFilerManager.CheckCanSend(_packet))
    {
        Send(_packet);
    }
}

void OnRecvPacket(const std::shared_ptr<PacketBase>& _packet)
{
    LOG_D("%d", _packet->GetIndex());
    SendFilerManager.OnRecv(_packet);
}

int main()
{
    auto packet = std::make_shared<PACKET_USE_ITEM_REQ>();
    TrySend(packet);
    TrySend(packet);

    return 0;
}