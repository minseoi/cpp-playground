/* Created by minseoi */

#include "PacketSendFilterDoOnce.h"

#include "Log/LogDefinition.h"

bool PacketSendFilterDoOnce::operator()(const bool isRecv)
{
    {
        if (!isRecv)
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
}
