#pragma once

#include <limits>
#include <type_traits>

namespace detail
{
    template<typename T>
    constexpr T sqrt_newton_rhapson(T x, T curr, T prev)
    {
        return curr == prev
                   ? curr
                   : sqrt_newton_rhapson(x, T{0.5} * (curr + x / curr), curr);
    }
} // namespace detail

namespace math
{
    template<typename T>
    constexpr T sqrt(T x)
    {
        if (x >= 0 && x < std::numeric_limits<T>::infinity())
        {
            return detail::sqrt_newton_rhapson(x, x, T{0});
        }

        return std::numeric_limits<T>::quiet_NaN();
    }
} // namespace math
