/* Created by minseoi */

#pragma once
#include <memory>
#include "Engine/Definition/TypeDefinition.h"

class World
{
private:
    uint8 bShouldTick : 1;

public:
    static std::unique_ptr<World> CreateWorld();
    explicit World();

    [[nodiscard]] bool ShouldTick() const { return bShouldTick; }
    void Tick(float DeltaSeconds);
};