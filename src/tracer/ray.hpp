#pragma once

#include "vector.hpp"

class Ray
{
public:
    constexpr Ray() = default;
    constexpr Ray(Point o, Vector d) : origin{o}, direction{d}
    {}

    constexpr Vector operator()(float t) const
    {
        return origin + t * direction;
    }

    Point origin;
    Vector direction;
};
