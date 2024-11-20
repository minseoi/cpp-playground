/* Created by minseoi */

#include "Math.h"

#include <valarray>

#include "Vector.hpp"

float Math::Dist(const Vector& V1, const Vector& V2)
{
    return Sqrt(DistSquared(V1, V2));
}

float Math::DistSquared(const Vector& V1, const Vector& V2)
{
    return Square(V2.X - V1.X) + Square(V2.Y - V1.Y) + Square(V2.Z - V1.Z);
}

float Math::Square(const float x)
{
    return x * x;
}

float Math::Sqrt(float x)
{
    return std::sqrt(x);
}
