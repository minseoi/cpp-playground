/* Created by minseoi */

#include "Actor.h"
#include "Math/Vector.hpp"

Actor::Actor(const Vector &_m_location) :
    m_location(_m_location)
{
}

Vector Actor::GetActorLocation() const
{
    return m_location;
}
