/* Created by minseoi */

#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Engine/Runtime/Core/Logging/LogMacros.h"
#include "Engine/Runtime/Engine/Classes/World/World.h"
#include "Engine/Runtime/Core/Misc/App.h"
#include "Subsystem/EngineSubsystemCollection.hpp"


class GameInstance;
class EngineLoop;

struct WorldContext
{
    std::shared_ptr<World> currentWorld;
    std::weak_ptr<GameInstance> owningGameInstance;

public:
    explicit WorldContext() :
    currentWorld(nullptr)
    {
    }

    void SetCurrentWorld(std::unique_ptr<World> InWorld)
    {
        currentWorld = std::move(InWorld);
    }

    inline std::shared_ptr<World> World()
    {
        return currentWorld;
    }
};

class Engine
{
public:
    EngineLoop* EngineLoopPtr;

protected:
    std::vector<std::shared_ptr<WorldContext>> m_worldList;
    std::shared_ptr<GameInstance> m_gameInstance;

private:
    EngineSubsystemCollection m_engineSubsystemCollection;

public:
    void Init(EngineLoop* InLoop);
    void Start();
    void Tick(float DeltaSeconds, bool bIdleMode);

    void LoadConfig();
    double CorrectNegativeTimeDelta(double DeltaRealTime);
    void UpdateTimeAndHandleMaxTickRate();

    WorldContext& CreateNewWorldContext();
};

extern Engine* GEngine;
