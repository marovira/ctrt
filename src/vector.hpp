#pragma once

#include "utils.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <type_traits>
#include <zeus/compiler.hpp>

template<typename T>
class Vector
{
public:
    std::array<T, 3> data;

    constexpr Vector() : data{0, 0, 0}
    {}

    constexpr explicit Vector(T x) : data{x, x, x}
    {}

    constexpr Vector(T x, T y, T z) : data{x, y, z}
    {}

    constexpr T& x()
    {
        return data[0];
    }

    constexpr T& r()
    {
        return x();
    }

    constexpr T x() const
    {
        return data[0];
    }

    constexpr T r() const
    {
        return x();
    }

    constexpr T& y()
    {
        return data[1];
    }

    constexpr T& g()
    {
        return y();
    }

    constexpr T y() const
    {
        return data[1];
    }

    constexpr T g() const
    {
        return y();
    }

    constexpr T& z()
    {
        return data[2];
    }

    constexpr T& b()
    {
        return z();
    }

    constexpr T z() const
    {
        return data[2];
    }

    constexpr T b() const
    {
        return z();
    }

    constexpr T operator[](std::size_t i) const
    {
        return data[i];
    }

    constexpr T& operator[](std::size_t i)
    {
        return data[i];
    }
};

template<typename T, typename UnaryOp>
constexpr Vector<T> unary_op(Vector<T>&& vec, UnaryOp&& fun)
{
    Vector<T> out{std::move(vec)};
    for (auto& val : out.data)
    {
        val = fun(val);
    }
    return out;
}

template<typename T, typename UnaryOp>
constexpr Vector<T> unary_op(Vector<T> const& vec, UnaryOp&& fun)
{
    Vector<T> out{vec};
    for (auto& val : out.data)
    {
        val = fun(val);
    }
    return out;
}

template<typename T, typename BinaryOp>
constexpr Vector<T>
binary_op(Vector<T>&& lhs, Vector<T> const& rhs, BinaryOp&& fun)
{
    Vector<T> out{std::move(lhs)};

    for (std::size_t i{0}; i < 3; ++i)
    {
        out.data[i] = fun(lhs.data[i], rhs.data[i]);
    }
    return out;
}

template<typename T, typename BinaryOp>
constexpr Vector<T>
binary_op(Vector<T> const& lhs, Vector<T> const& rhs, BinaryOp&& fun)
{
    Vector<T> out{lhs};
    for (std::size_t i{0}; i < 3; ++i)
    {
        out.data[i] = fun(lhs.data[i], rhs.data[i]);
    }
    return out;
}

template<typename T>
constexpr bool operator==(Vector<T> const& lhs, Vector<T> const& rhs)
{
    return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == lhs.z();
}

template<typename T>
constexpr bool operator!=(Vector<T> const& lhs, Vector<T> const& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
constexpr Vector<T> operator-(Vector<T> const& vec)
{
    return unary_op(vec, [](T a) { return -a; });
}

template<typename T>
constexpr Vector<T>& operator+=(Vector<T>& lhs, Vector<T> const& rhs)
{
    lhs = binary_op(std::move(lhs), rhs, [](T a, T b) { return a + b; });
    return lhs;
}

template<typename T>
constexpr Vector<T>& operator-=(Vector<T>& lhs, Vector<T> const& rhs)
{
    lhs = binary_op(std::move(lhs), rhs, [](T a, T b) { return a - b; });
    return lhs;
}

template<typename T>
constexpr Vector<T>& operator*=(Vector<T>& lhs, T rhs)
{
    lhs = unary_op(std::move(lhs), [rhs](T a) { return a * rhs; });
    return lhs;
}

template<typename T>
constexpr Vector<T>& operator/=(Vector<T>& lhs, T rhs)
{
    lhs = unary_op(std::move(lhs), [rhs](T a) { return a / rhs; });
    return lhs;
}

template<typename T>
constexpr Vector<T> operator+(Vector<T> const& lhs, Vector<T> const& rhs)
{
    Vector<T> out{lhs};
    out += rhs;
    return out;
}

template<typename T>
constexpr Vector<T> operator-(Vector<T> const& lhs, Vector<T> const& rhs)
{
    Vector<T> out{lhs};
    out -= rhs;
    return out;
}

template<typename T>
constexpr Vector<T> operator*(Vector<T> const& lhs, Vector<T> const& rhs)
{
    Vector<T> out = binary_op(lhs, rhs, [](T a, T b) { return a * b; });
    return out;
}

template<typename T>
constexpr Vector<T> operator*(Vector<T> const& lhs, T rhs)
{
    Vector<T> out{lhs};
    out *= rhs;
    return out;
}

template<typename T>
constexpr Vector<T> operator*(T lhs, Vector<T> const& rhs)
{
    Vector<T> out{rhs};
    out *= lhs;
    return out;
}

template<typename T>
constexpr Vector<T> operator/(Vector<T> const& lhs, T rhs)
{
    Vector<T> out{lhs};
    out /= rhs;
    return out;
}

template<typename T>
constexpr T dot(Vector<T> const& lhs, Vector<T> const& rhs)
{
    return (lhs.x() * rhs.x()) + (lhs.y() * rhs.y()) + (lhs.z() * rhs.z());
}

template<typename T>
constexpr T length(Vector<T> const& vec)
{
    return static_cast<T>(utils::sqrt(dot(vec, vec)));
}

template<typename T>
constexpr T length_squared(Vector<T> const& vec)
{
    return dot(vec, vec);
}

template<typename T>
constexpr Vector<T> cross(Vector<T> const& u, Vector<T> const& v)
{
    return Vector<T>{(u.y() * v.z()) - (u.z() * v.y()),
                     (u.z() * v.x()) - (u.x() * v.z()),
                     (u.x() * v.y()) - (u.y() * v.x())};
}

template<typename T>
constexpr Vector<T> unit_vector(Vector<T> const& v)
{
    Vector<T> out{v};
    out /= length(v);
    return out;
}

using Vectorf = Vector<float>;
using Vectord = Vector<double>;

template<typename T>
using Point  = Vector<T>;
using Pointf = Point<float>;
using Pointd = Point<double>;

template<typename T>
using Colour  = Vector<T>;
using Colourf = Colour<float>;
using Colourd = Colour<double>;
