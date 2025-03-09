/* Created by minseoi */

#pragma once
#include <memory>
#include <tuple>

#include "ISubsystemCollection.hpp"
#include "SubsystemBase.h"

template <class... Args>
class SubsystemCollection : public ISubsystemCollection
{
    static_assert((std::is_base_of_v<SubsystemBase, Args> && ...),
                      "All types in Args must derive from SubsystemBase");

    std::tuple<std::unique_ptr<Args>...> m_subsystemTuple;

public:
    SubsystemCollection() :
        m_subsystemTuple(std::make_unique<Args>()...)
    {
    }

    void Initialize()
    {
        std::apply([this](auto&... subsystems) {
            (InitializeOne(*subsystems), ...);
        }, m_subsystemTuple);
    }

    template<class T>
    T* GetSubSystem() const
    {
        return std::get<std::unique_ptr<T>>(m_subsystemTuple).get();
    }

    template <typename T>
    void InitializeDependency()
    {
        T* subsystem = GetSubSystem<T>();
        if (subsystem && !subsystem->IsInitialized())
        {
            InitializeOne(*subsystem);
        }
    }

private:
    void InitializeOne(SubsystemBase& subsystem)
    {
        if (!subsystem.IsInitialized())
        {
            subsystem.Initialize(*this);
        }
    }
};
