#pragma once

#include "ray.hpp"

class Camera
{
public:
    constexpr Camera() : m_distance{0.0f}
    {}

    constexpr Camera(Pointf const& eye,
                     Vectorf const& look_at,
                     Vectorf const& up,
                     float distance) :
        m_distance{distance}
    {
        m_w = unit_vector(eye - look_at);
        m_u = unit_vector(cross(up, m_w));
        m_v = cross(m_w, m_u);
    }

    constexpr Vectorf get_ray_direction(Pointf const& p) const
    {
        auto dir = p.x() * m_u + p.y() * m_v - m_distance * m_w;
        return unit_vector(dir);
    }

private:
    Vectorf m_u, m_v, m_w;
    float m_distance;
};
