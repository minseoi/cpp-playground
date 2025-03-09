/* Created by minseoi */

#pragma once
#include <memory>
#include <tuple>

#include "SubsystemBase.h"

class ISubsystemCollection
{
public:
    virtual ~ISubsystemCollection() = default;

    template <typename T>
    T* GetSubSystem() const
    {
        return nullptr;
    }

    template <typename T>
    void InitializeDependency()
    {
    }
};
