/* Created by minseoi */

#pragma once


class ISubsystemCollection;

class SubsystemBase
{
private:
    bool m_initialized {};

public:
    virtual ~SubsystemBase() = default;

    [[nodiscard]] bool IsInitialized() const;
    virtual void Initialize(ISubsystemCollection& _subsystemCollection);
};
