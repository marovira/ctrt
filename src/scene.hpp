#pragma once

#include "camera.hpp"
#include "ray.hpp"
#include "vector.hpp"

template<typename T>
class Scene
{
    constexpr Scene(Camera const& camera) : m_camera{camera}
    {}

    friend T;

public:
    constexpr Camera get_camera() const
    {
        return m_camera;
    }

    constexpr Colourf trace(Rayf const& ray) const
    {
        return static_cast<T const&>(*this).trace(ray);
    }

private:
    Camera m_camera;
};

class FirstScene : public Scene<FirstScene>
{
public:
    constexpr FirstScene(Camera const& camera) : Scene{camera}
    {}

    constexpr Colourf trace(Rayf const& ray) const
    {
        float t = 0.5f * (ray.direction.y() + 1.0f);
        return (1.0f - t) * Colourf{1.0f, 1.0f, 1.0f} +
               t * Colourf{0.5f, 0.7f, 1.0f};
    }
};
