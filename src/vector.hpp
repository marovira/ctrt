#pragma once

#include "utils.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <type_traits>
#include <zeus/compiler.hpp>

class Vector
{
public:
    std::array<float, 3> data;

    constexpr Vector() : data{0, 0, 0}
    {}

    constexpr explicit Vector(float x) : data{x, x, x}
    {}

    constexpr Vector(float x, float y, float z) : data{x, y, z}
    {}

    constexpr float& x()
    {
        return data[0];
    }

    constexpr float& r()
    {
        return x();
    }

    constexpr float x() const
    {
        return data[0];
    }

    constexpr float r() const
    {
        return x();
    }

    constexpr float& y()
    {
        return data[1];
    }

    constexpr float& g()
    {
        return y();
    }

    constexpr float y() const
    {
        return data[1];
    }

    constexpr float g() const
    {
        return y();
    }

    constexpr float& z()
    {
        return data[2];
    }

    constexpr float& b()
    {
        return z();
    }

    constexpr float z() const
    {
        return data[2];
    }

    constexpr float b() const
    {
        return z();
    }

    constexpr float operator[](std::size_t i) const
    {
        return data[i];
    }

    constexpr float& operator[](std::size_t i)
    {
        return data[i];
    }
};

constexpr bool operator==(Vector const& lhs, Vector const& rhs)
{
    return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == lhs.z();
}

constexpr bool operator!=(Vector const& lhs, Vector const& rhs)
{
    return !(lhs == rhs);
}

constexpr Vector operator-(Vector const& vec)
{
    return {-vec.x(), -vec.y(), -vec.z()};
}

constexpr Vector& operator+=(Vector& lhs, Vector const& rhs)
{
    lhs.x() += rhs.x();
    lhs.y() += rhs.y();
    lhs.z() += rhs.z();

    return lhs;
}

constexpr Vector& operator-=(Vector& lhs, Vector const& rhs)
{
    lhs.x() -= rhs.x();
    lhs.y() -= rhs.y();
    lhs.z() -= rhs.z();

    return lhs;
}

constexpr Vector& operator*=(Vector& lhs, Vector const& rhs)
{
    lhs.x() *= rhs.x();
    lhs.y() *= rhs.y();
    lhs.z() *= rhs.z();

    return lhs;
}

constexpr Vector& operator*=(Vector& lhs, float rhs)
{
    lhs.x() *= rhs;
    lhs.y() *= rhs;
    lhs.z() *= rhs;

    return lhs;
}

constexpr Vector& operator/=(Vector& lhs, float rhs)
{
    lhs.x() /= rhs;
    lhs.y() /= rhs;
    lhs.z() /= rhs;

    return lhs;
}

constexpr Vector operator+(Vector const& lhs, Vector const& rhs)
{
    Vector out{lhs};
    out += rhs;
    return out;
}

constexpr Vector operator-(Vector const& lhs, Vector const& rhs)
{
    Vector out{lhs};
    out -= rhs;
    return out;
}

constexpr Vector operator*(Vector const& lhs, Vector const& rhs)
{
    Vector out{lhs};
    out *= rhs;
    return out;
}

constexpr Vector operator*(Vector const& lhs, float rhs)
{
    Vector out{lhs};
    out *= rhs;
    return out;
}

constexpr Vector operator*(float lhs, Vector const& rhs)
{
    Vector out{rhs};
    out *= lhs;
    return out;
}

constexpr Vector operator/(Vector const& lhs, float rhs)
{
    Vector out{lhs};
    out /= rhs;
    return out;
}

constexpr float dot(Vector const& lhs, Vector const& rhs)
{
    return (lhs.x() * rhs.x()) + (lhs.y() * rhs.y()) + (lhs.z() * rhs.z());
}

constexpr float length(Vector const& vec)
{
    return utils::sqrt(dot(vec, vec));
}

constexpr float length_squared(Vector const& vec)
{
    return dot(vec, vec);
}

constexpr Vector cross(Vector const& u, Vector const& v)
{
    return Vector{(u.y() * v.z()) - (u.z() * v.y()),
                  (u.z() * v.x()) - (u.x() * v.z()),
                  (u.x() * v.y()) - (u.y() * v.x())};
}

constexpr Vector normalise(Vector const& v)
{
    Vector out{v};
    out /= length(v);
    return out;
}

using Point  = Vector;
using Normal = Vector;
using Colour = Vector;
