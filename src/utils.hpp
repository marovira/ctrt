#pragma once

#include <limits>
#include <type_traits>

namespace utils
{
    namespace detail
    {
        // Adapted from https://gist.github.com/alexshtf/eb5128b3e3e143187794
        template<typename T>
        constexpr T sqrt_newton_rhapson(T x, T curr, T prev)
        {
            return curr == prev ? curr
                                : sqrt_newton_rhapson(
                                      x, T{0.5} * (curr + x / curr), curr);
        }
    } // namespace detail

    template<typename T>
    constexpr T sqrt(T x)
    {
        if (x >= 0 && x < std::numeric_limits<T>::infinity())
        {
            return detail::sqrt_newton_rhapson(x, x, T{0});
        }

        return std::numeric_limits<T>::quiet_NaN();
    }

    // Taken from FluentC++
    // https://www.fluentcpp.com/2017/05/19/crtp-helper/
    template<typename T, template<typename> class crtpType>
    class StaticBase
    {
        StaticBase() = default;
        friend crtpType<T>;

    public:
        constexpr T& self()
        {
            return static_cast<T&>(*this);
        }

        constexpr T const& self() const
        {
            return static_cast<T const&>(*this);
        }
    };

    template<typename T, typename... Args>
    struct Contains
        : public std::bool_constant<(std::is_same<T, Args>{} || ...)>
    {};
} // namespace utils
