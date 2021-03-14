#pragma once

#include "vector.hpp"

template<typename T>
class Ray
{
public:
    constexpr Ray() = default;
    constexpr Ray(Point<T> o, Vector<T> d) : origin{o}, direction{d}
    {}

    constexpr Vector<T> operator()(T t) const
    {
        return origin + t * direction;
    }

    Point<T> origin;
    Vector<T> direction;
};

using Rayf = Ray<float>;
using Rayd = Ray<double>;
