/* Created by minseoi */

#include "SubsystemBase.h"

bool SubsystemBase::IsInitialized() const
{
    return m_initialized;
}

void SubsystemBase::Initialize(ISubsystemCollection &_subsystemCollection)
{
    m_initialized = true;
}