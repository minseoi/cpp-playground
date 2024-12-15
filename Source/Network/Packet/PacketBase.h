/* Created by minseoi */

#pragma once

#include "Network/NetworkDefinition.h"

class PacketBase
{
    PACKET_INDEX m_index {};

public:
    PACKET_INDEX GetIndex();
};
