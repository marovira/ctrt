#pragma once

#include "ray.hpp"

class Camera
{
public:
    constexpr Camera() : m_distance{0.0f}
    {}

    constexpr Camera(Point const& eye,
                     Vector const& look_at,
                     Vector const& up,
                     float distance) :
        m_distance{distance}
    {
        m_w = normalise(eye - look_at);
        m_u = normalise(cross(up, m_w));
        m_v = cross(m_w, m_u);
    }

    constexpr Vector get_ray_direction(Point const& p) const
    {
        auto dir = p.x() * m_u + p.y() * m_v - m_distance * m_w;
        return normalise(dir);
    }

private:
    Vector m_u, m_v, m_w;
    float m_distance;
};
