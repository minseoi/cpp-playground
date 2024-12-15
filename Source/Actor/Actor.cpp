/* Created by minseoi */

#include "Actor.h"
#include "Math/Vector.hpp"

Actor::Actor() :
    m_location(Vector::ZeroVector)
{
}

Vector Actor::GetActorLocation() const
{
    return m_location;
}

void Actor::SetActorLocation(const Vector &location)
{
    m_location = location;
}
