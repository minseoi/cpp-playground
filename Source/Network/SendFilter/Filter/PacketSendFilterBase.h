/* Created by minseoi */

#pragma once


class PacketSendFilterBase
{
public:
    explicit PacketSendFilterBase() = default;
    virtual ~PacketSendFilterBase() = default;

    virtual bool operator()(const bool isRecv) = 0;
};
