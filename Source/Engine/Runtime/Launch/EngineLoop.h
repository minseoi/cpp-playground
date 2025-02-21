/* Created by minseoi */

#pragma once
#include "Engine/Definition/TypeDefinition.h"
#include "Engine/Runtime/Core/CoreGlobals.h"

class EngineLoop
{
public:
    int32 Init();
    void Tick();
    void Exit();
};