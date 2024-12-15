/* Created by minseoi */

#pragma once

struct Vector
{
    float X;
    float Y;
    float Z;

    Vector(const float _x, const float _y, const float _z) :
        X(_x),
        Y(_y),
        Z(_z)
    {
    }

    Vector(const Vector& other) = default;

    Vector operator + (const Vector& other) const {
        return {X + other.X, Y + other.Y, Z + other.Z};
    }

    Vector operator - (const Vector& other) const {
        return {X - other.X, Y - other.Y, Z - other.Z};
    }

    Vector operator * (const float scalar) const {
        return {X * scalar, Y * scalar, Z * scalar};
    }

    Vector& operator += (const Vector& other) {
        X += other.X; Y += other.Y; Z += other.Z;
        return *this;
    }

    static Vector ZeroVector;
};

inline Vector Vector::ZeroVector = {0, 0, 0};