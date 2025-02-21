/* Created by minseoi */

#include "World.h"

std::unique_ptr<World> World::CreateWorld()
{
    auto newWorld = std::make_unique<World>();
    return newWorld;
}

World::World()
{
}
