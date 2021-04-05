#pragma once

#include "brdf.hpp"
#include "shapes.hpp"

#include <variant>

template<typename T>
class Material : public utils::StaticBase<T, Material>
{
public:
    constexpr Material()
    {}

    template<class LightContainer, class ShapeContainer>
    constexpr Colour shade(ShadeRec const& rec,
                           LightContainer const& lights,
                           ShapeContainer const& shapes) const
    {
        return this->self().shade(rec, lights, shapes);
    }
};

class EmptyMaterial : public Material<EmptyMaterial>
{
public:
    constexpr EmptyMaterial()
    {}

    template<class LightContainer, class ShapeContainer>
    constexpr Colour shade(ShadeRec const& rec,
                           LightContainer const&,
                           ShapeContainer const&) const
    {
        return rec.default_colour;
    }
};

class Matte : public Material<Matte>
{
public:
    constexpr Matte()
    {}

    template<class LightContainer, class ShapeContainer>
    constexpr Colour shade(ShadeRec const& rec,
                           LightContainer const& lights,
                           ShapeContainer const& shapes) const
    {
        Vector wo = -rec.ray.origin;
        Colour L  = m_ambient_brdf.rho(rec, wo) * lights[0].l(rec);

        if (lights.size() == 1)
        {
            return L;
        }

        for (std::size_t i{1}; i < lights.size(); ++i)
        {
            Vector wi      = lights[i].get_direction(rec);
            float n_dot_wi = dot(rec.normal, wi);

            if (n_dot_wi > 0.0f)
            {
                bool in_shadow{false};
                if (lights[i].casts_shadows())
                {
                    Ray shadow_ray{rec.hit_point, wi};
                    float d =
                        distance(shadow_ray.origin, lights[i].get_position());
                    for (auto const& shape : shapes)
                    {
                        if (auto result = shape.shadow_hit(shadow_ray); result)
                        {
                            if (*result < d)
                            {
                                in_shadow = true;
                                break;
                            }
                        }
                    }
                }

                if (!in_shadow)
                {
                    L += m_diffuse_brdf.fn(rec, wo, wi) * lights[i].l(rec) *
                         n_dot_wi;
                }
            }
        }

        return L;
    }

    constexpr void set_diffuse_reflection(float k)
    {
        m_diffuse_brdf.set_diffuse_reflection(k);
    }

    constexpr void set_ambient_reflection(float k)
    {
        m_ambient_brdf.set_diffuse_reflection(k);
    }

    constexpr void set_diffuse_colour(Colour const& colour)
    {
        m_ambient_brdf.set_diffuse_colour(colour);
        m_diffuse_brdf.set_diffuse_colour(colour);
    }

private:
    Lambertian m_diffuse_brdf{};
    Lambertian m_ambient_brdf{};
};

template<class... Materials>
class MaterialWrapper
{
public:
    constexpr MaterialWrapper()
    {}

    template<typename T, typename = utils::Contains<T, Materials...>>
    constexpr MaterialWrapper(T&& elem) : m_material{std::forward<T>(elem)}
    {}

    template<class LightContainer, class ShapeContainer>
    constexpr Colour shade(ShadeRec const& rec,
                           LightContainer const& lights,
                           ShapeContainer const& shapes) const
    {
        return std::visit(
            [rec, &lights, &shapes](auto const& elem) {
                return elem.shade(rec, lights, shapes);
            },
            m_material);
    }

private:
    std::variant<Materials...> m_material;
};

using Materials = MaterialWrapper<EmptyMaterial, Matte>;
