/* Created by minseoi */

#pragma once
#include <memory>
#include "Math/Vector.hpp"


struct Vector;

class Actor : std::enable_shared_from_this<Actor>
{
    Vector m_location;

public:
    explicit Actor(const Vector &_m_location);

    Vector GetActorLocation() const;
};
