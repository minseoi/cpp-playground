/* Created by minseoi */

#pragma once
#include "PacketSendFilterBase.h"


class PacketSendFilterDoOnce final : public PacketSendFilterBase
{
private:
    bool m_allow {};

public:
    explicit PacketSendFilterDoOnce() :
        PacketSendFilterBase()
    {
    }

    bool operator() (const bool isRecv) override;
};
