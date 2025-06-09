/* Created by minseoi */

#include "EngineLoop.h"
#include "Engine/Runtime/Engine/Engine.h"

int32 EngineLoop::Init()
{
    GEngine = new Engine();
    if (!GEngine)
    {
        return -1;
    }

    GEngine->Init(this);

    GEngine->Start();

    LOG_I("Engine is initialized.");
    return 0;
}

void EngineLoop::Tick()
{
    GEngine->UpdateTimeAndHandleMaxTickRate();

    {
        bool bIdleMode = false;
        // main game engine tick
        GEngine->Tick(App::GetDeltaTime(), bIdleMode);
    }
}

void EngineLoop::Exit()
{
}
