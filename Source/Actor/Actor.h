/* Created by minseoi */

#pragma once
#include <memory>
#include "Math/Vector.hpp"


struct Vector;

class Actor : std::enable_shared_from_this<Actor>
{
    Vector m_location;

public:
    explicit Actor();
    virtual ~Actor() = default;

    Vector GetActorLocation() const;
    void SetActorLocation(const Vector& location);
};
