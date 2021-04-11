#pragma once

#include <limits>
#include <type_traits>

namespace utils
{
    // Adapted from https://gist.github.com/alexshtf/eb5128b3e3e143187794
    constexpr float sqrt(float x)
    {
        if (x >= 0 && x < std::numeric_limits<float>::infinity())
        {
            float curr{x}, prev{0.0f};
            while (curr != prev)
            {
                prev = curr;
                curr = 0.5f * (curr + x / curr);
            }

            return curr;
        }

        return std::numeric_limits<float>::quiet_NaN();
    }

    constexpr float pow(float base, int exp)
    {
        float ret{1.0f};
        for (int i{0}; i < exp; ++i)
        {
            ret *= base;
        }

        return base;
    }

    constexpr float abs(float x)
    {
        return (x < 0.0f) ? -x : x;
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
