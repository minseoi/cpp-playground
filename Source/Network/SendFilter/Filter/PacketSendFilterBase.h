/* Created by minseoi */

#pragma once


class PacketSendFilterBase
{
    virtual ~PacketSendFilterBase() = default;

    virtual void OnSend() = 0;
    virtual void OnRecv() = 0;
};
