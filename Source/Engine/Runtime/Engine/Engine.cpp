/* Created by minseoi */

#include "Engine.h"

#include <fstream>
#include <thread>
#include <algorithm>

#include "Classes/GameInstance.h"
#include "Engine/Runtime/Core/GenericPlatform/GenericPlatformTime.h"
#include "Engine/Runtime/Launch/EngineLoop.h"

Engine* GEngine = nullptr;

void Engine::Init(EngineLoop* InLoop)
{
    EngineLoopPtr = InLoop;

    m_engineSubsystemCollection.Initialize();

    // WorldContext &InitialWorldContext = CreateNewWorldContext();
    // InitialWorldContext.SetCurrentWorld(World::CreateWorld());

    m_gameInstance = std::make_shared<GameInstance>();
    m_gameInstance->InitializeStandalone();
}

void Engine::Start()
{
    LOG_I("Starting Game");
    m_gameInstance->StartGameInstnace();
}

void Engine::Tick(float DeltaSeconds, bool bIdleMode)
{
    for (int32 WorldIdx = 0; WorldIdx < m_worldList.size(); ++WorldIdx)
    {
        std::shared_ptr<WorldContext>& Context = m_worldList[WorldIdx];
        if (Context == nullptr || Context->World() == nullptr || !Context->World()->ShouldTick())
        {
            continue;
        }

        if (!bIdleMode)
        {
            // Tick the world.
            Context->World()->Tick(DeltaSeconds );
        }
    }
}

double Engine::CorrectNegativeTimeDelta(double DeltaRealTime)
{
    LOG_W("Detected negative delta time - ignoring");
    return 0.01;
}

void Engine::UpdateTimeAndHandleMaxTickRate()
{
    static double LastRealTime = GenericPlatformTime::Seconds() - 0.0001;

    //todo: 고정 프레임
    //bool bUseFixedTimeStep = false;

    double CurrentRealTime = GenericPlatformTime::Seconds();
    App::SetCurrentTime(CurrentRealTime);

    float DeltaRealTime = CurrentRealTime - LastRealTime;
    if (DeltaRealTime < 0)
    {
        DeltaRealTime = CorrectNegativeTimeDelta(DeltaRealTime);
    }

    const float MaxTickRate = 30; //todo: 엔진한테 값 받아오기
    float WaitTime = 0;
    if( MaxTickRate > 0 )
    {
        WaitTime = std::max( 1.f / MaxTickRate - DeltaRealTime, 0.f);
    }
    if (WaitTime > 0)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<uint32>(WaitTime * 1000000.0f)));
        CurrentRealTime = GenericPlatformTime::Seconds();
        App::SetCurrentTime(CurrentRealTime);
    }

    App::SetDeltaTime(App::GetCurrentTime() - LastRealTime);
    LastRealTime = CurrentRealTime;
}

WorldContext& Engine::CreateNewWorldContext()
{
    WorldContext* NewWorldContext = new WorldContext();
    m_worldList.emplace_back(NewWorldContext);

    return *NewWorldContext;
}
