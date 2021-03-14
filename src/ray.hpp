#pragma once

#include "vector.hpp"

namespace math
{
    template<typename T>
    class Ray
    {
    public:
        constexpr Ray() = default;
        constexpr Ray(math::Point<T> o, math::Vector<T> d) :
            origin{o}, direction{d}
        {}

        constexpr math::Vector<T> operator()(T t) const
        {
            return origin + t * direction;
        }

        math::Point<T> origin;
        math::Point<T> direction;
    };

    using Rayf = Ray<float>;
    using Rayd = Ray<double>;
} // namespace math
