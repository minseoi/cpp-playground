/* Created by minseoi */

#pragma once
#include <memory>
#include <string>

class World
{
public:
    static std::unique_ptr<World> CreateWorld();
    explicit World();
};