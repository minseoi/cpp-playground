/* Created by minseoi */

#include "World.h"

#include "Engine/Runtime/Core/Logging/LogMacros.h"

std::unique_ptr<World> World::CreateWorld()
{
    auto newWorld = std::make_unique<World>();
    return newWorld;
}

World::World() :
    bShouldTick(true)
{
}

void World::Tick(float DeltaSeconds)
{
    LOG_D("world tick : %f", DeltaSeconds);
}
