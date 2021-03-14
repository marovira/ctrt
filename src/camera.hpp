#pragma once

#include "ray.hpp"

template<std::size_t width, std::size_t height>
class Camera
{
public:
    constexpr Rayf get_ray(std::size_t row, std::size_t col) const
    {
        float u = static_cast<float>(row) / (width - 1);
        float v = static_cast<float>(col) / (height - 1);

        Rayf ray{m_origin,
                 m_lower_left + (u * m_right) + (v * m_up) - m_origin};
        return ray;
    }

private:
    float m_viewport_height{2.0f};
    float m_aspect_ratio{static_cast<float>(width) / height};
    float m_viewport_width{m_aspect_ratio * m_viewport_height};
    float m_focal_length{1.0f};

    Vectorf m_origin{0.0f};
    Vectorf m_right{m_viewport_width, 0.0f, 0.0f};
    Vectorf m_up{0.0f, m_viewport_height, 0.0f};
    Vectorf m_lower_left{m_origin - (m_right / 2.0f) - (m_up / 2.0f) -
                         Vectorf{0.0f, 0.0f, m_focal_length}};
};
