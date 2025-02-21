/* Created by minseoi */

#pragma once
#include "Engine/Runtime/Launch/EngineLoop.h"

EngineLoop GEngineLoop;

int32 EngineInit()
{
    int32 ErrorLevel = GEngineLoop.Init();

    return( ErrorLevel );
}

void EngineTick()
{
    GEngineLoop.Tick();
}

void EngineExit()
{
    GEngineLoop.Exit();
}

int32 GuardedMain()
{
    struct EnginCleanupGuard
    {
        ~EnginCleanupGuard()
        {
            EngineExit();
        }
    } CleanupGuard;

    int32 ErrorLevel = EngineInit();

    while( !IsEngineExitRequested() )
    {
        EngineTick();
    }

    return ErrorLevel;
}