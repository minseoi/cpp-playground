#include <iostream>
#include "Log/LogDefinition.h"

using PACKET_INDEX = unsigned int;

#define PACKET_USE_ITEM_REQ_INDEX 1000
#define PACKET_USE_ITEM_ACK_INDEX 1001

class PacketBase
{
    PACKET_INDEX m_index {};

public:
    explicit PacketBase(PACKET_INDEX _packetIndex) :
        m_index(_packetIndex)
    {
    }
    explicit PacketBase() = delete;
    virtual ~PacketBase() = default;
    [[nodiscard]] PACKET_INDEX GetIndex() const
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
    PacketBase(PACKET_USE_ITEM_ACK_INDEX)
    {
    }
};
class PACKET_USE_ITEM_REQ final : public PacketBase
{
public:
    PACKET_USE_ITEM_REQ() :
    PacketBase(PACKET_USE_ITEM_REQ_INDEX)
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

    virtual bool TrySend() = 0;
    virtual void OnRecv() = 0;
};

class PacketSendFilter_DoOnce final : public PacketSendFilterBase
{
private:
    bool bSnet;

public:
    explicit PacketSendFilter_DoOnce() :
        PacketSendFilterBase(),
        bSnet(false)
    {
    }

    bool TrySend() override
    {
        if (bSnet)
        {
            LOG_I("Block");
            return false;
        }

        bSnet = true;
        LOG_I("Allow");
        return true;
    }

    void OnRecv() override
    {
        bSnet = false;
    }
};


class PakcetSendFilterManager
{
private:
    std::unordered_map<PACKET_INDEX, std::shared_ptr<PacketSendFilterBase>> m_filterMap;

public:
    explicit PakcetSendFilterManager()
    {
        m_filterMap.clear();
        m_filterMap.emplace(PACKET_USE_ITEM_REQ_INDEX, std::make_shared<PacketSendFilter_DoOnce>());
    }

    bool CheckCanSend(const std::shared_ptr<PacketBase>& _packet)
    {
        if (const std::shared_ptr<PacketSendFilterBase>& Filter = GetFiler(_packet))
        {
            return Filter->TrySend();
        }
        return true;
    }

    void OnRecv(const std::shared_ptr<PacketBase>& _packet)
    {
        if (const std::shared_ptr<PacketSendFilterBase>& Filter = GetFiler(_packet))
        {
            return Filter->OnRecv();
        }
    }

private:
    std::shared_ptr<PacketSendFilterBase> GetFiler(const std::shared_ptr<PacketBase>& _packet)
    {
        if (_packet == nullptr)
        {
            return {};
        }

        const auto iter = m_filterMap.find(_packet->GetIndex());
        if (iter == m_filterMap.end())
        {
            return {};
        }

        return iter->second;
    }
};

// ****************************************************************************** //

PakcetSendFilterManager SendFilerManager;

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