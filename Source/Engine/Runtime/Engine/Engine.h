/* Created by minseoi */

#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Engine/Runtime/Core/Logging/LogMacros.h"
#include "Engine/Runtime/World/World.h"
#include "Engine/Runtime/Core/Misc/App.h"


class EngineLoop;

struct WorldContext
{
private:
    std::shared_ptr<World> currentWorld;

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
    std::vector<std::shared_ptr<WorldContext>> WorldList;

public:
    void Init(EngineLoop* InLoop);
    void Start();
    void Tick(float DeltaSeconds, bool bIdleMode);

    double CorrectNegativeTimeDelta(double DeltaRealTime);
    void UpdateTimeAndHandleMaxTickRate();

    WorldContext& CreateNewWorldContext();
};

extern Engine* GEngine;
