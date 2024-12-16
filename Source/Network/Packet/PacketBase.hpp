/* Created by minseoi */

#pragma once

#include "PacketDefinition.h"
#include "Network/NetworkDefinition.h"

class PacketBase
{
    PacketIndex m_index {};

public:
    explicit PacketBase(PacketIndex packetIndex) :
        m_index(packetIndex)
    {
    }
    explicit PacketBase() = delete;
    virtual ~PacketBase() = default;

    [[nodiscard]] PacketIndex GetIndex() const
    {
        return m_index;
    }
};
