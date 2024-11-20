/* Created by minseoi */

#pragma once

struct Vector;

class Math
{
public:
    static float Dist(const Vector& A, const Vector& B);

    static float DistSquared(const Vector &V1, const Vector &V2);

    static float Square(float x);

    static float Sqrt(float x);
};
