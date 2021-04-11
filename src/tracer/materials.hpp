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

    template<class LightContainer,
             class ShapeContainer,
             class MaterialContainer>
    constexpr Colour shade(ShadeRec const& rec,
                           LightContainer const& lights,
                           ShapeContainer const& shapes,
                           MaterialContainer const& materials) const
    {
        return this->self().shade(rec, lights, shapes, materials);
    }
};

class EmptyMaterial : public Material<EmptyMaterial>
{
public:
    constexpr EmptyMaterial()
    {}

    template<class LightContainer,
             class ShapeContainer,
             class MaterialContainer>
    constexpr Colour shade(ShadeRec const& rec,
                           LightContainer const&,
                           ShapeContainer const&,
                           MaterialContainer const&) const
    {
        return rec.default_colour;
    }
};

class Matte : public Material<Matte>
{
public:
    constexpr Matte()
    {}

    template<class LightContainer,
             class ShapeContainer,
             class MaterialContainer>
    constexpr Colour shade(ShadeRec const& rec,
                           LightContainer const& lights,
                           ShapeContainer const& shapes,
                           MaterialContainer const&) const
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

class Phong : public Material<Phong>
{
public:
    constexpr Phong()
    {}

    template<class LightContainer,
             class ShapeContainer,
             class MaterialContainer>
    constexpr Colour shade(ShadeRec const& rec,
                           LightContainer const& lights,
                           ShapeContainer const& shapes,
                           MaterialContainer const&) const
    {
        Vector wo = -rec.ray.direction;
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
                    L += (m_diffuse_brdf.fn(rec, wo, wi) +
                          m_specular_brdf.fn(rec, wo, wi)) *
                         lights[i].l(rec) * n_dot_wi;
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

    constexpr void set_specular_reflection(float ks)
    {
        m_specular_brdf.set_specular_reflection(ks);
    }

    constexpr void set_specular_exponent(int exp)
    {
        m_specular_brdf.set_specular_exponent(exp);
    }

    constexpr void set_specular_colour(Colour const& col)
    {
        m_specular_brdf.set_specular_colour(col);
    }

private:
    Lambertian m_ambient_brdf{};
    Lambertian m_diffuse_brdf{};
    GlossySpecular m_specular_brdf{};
};

class Reflective : public Material<Reflective>
{
public:
    constexpr Reflective()
    {}

    template<class LightContainer,
             class ShapeContainer,
             class MaterialContainer>
    constexpr Colour shade(ShadeRec const& sr,
                           LightContainer const& lights,
                           ShapeContainer const& shapes,
                           MaterialContainer const& materials) const
    {
        if (sr.reflection_depth > ShadeRec::max_reflection_depth)
        {
            return Colour{0.0f};
        }

        // Direct illumination first.
        Colour L = m_phong.shade(sr, lights, shapes, materials);

        Vector wo     = -sr.ray.direction;
        auto [fr, wi] = m_reflective_brdf.sample_fn(sr, wo);
        Ray reflected_ray{sr.hit_point, wi};

        Colour reflected_colour;
        for (auto const& shape : shapes)
        {
            if (auto result = shape.hit(reflected_ray); result)
            {
                auto rec             = *result;
                rec.reflection_depth = sr.reflection_depth + 1;
                reflected_colour     = materials[rec.material_id].shade(
                    rec, lights, shapes, materials);
                break;
            }
        }

        L += fr * reflected_colour * dot(sr.normal, wi);

        return L;
    }

    constexpr void set_diffuse_reflection(float k)
    {
        m_phong.set_diffuse_reflection(k);
    }

    constexpr void set_ambient_reflection(float k)
    {
        m_phong.set_diffuse_reflection(k);
    }

    constexpr void set_diffuse_colour(Colour const& colour)
    {
        m_phong.set_diffuse_colour(colour);
        m_phong.set_diffuse_colour(colour);
    }

    constexpr void set_specular_reflection(float ks)
    {
        m_phong.set_specular_reflection(ks);
    }

    constexpr void set_specular_exponent(int exp)
    {
        m_phong.set_specular_exponent(exp);
    }

    constexpr void set_specular_colour(Colour const& col)
    {
        m_phong.set_specular_colour(col);
    }

    constexpr void set_reflection_coeff(float kr)
    {
        m_reflective_brdf.set_reflection_coeff(kr);
    }

    constexpr void set_reflection_colour(Colour const& col)
    {
        m_reflective_brdf.set_reflection_colour(col);
    }

private:
    Phong m_phong;
    PerfectSpecular m_reflective_brdf;
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

    template<class LightContainer,
             class ShapeContainer,
             class MaterialContainer>
    constexpr Colour shade(ShadeRec const& rec,
                           LightContainer const& lights,
                           ShapeContainer const& shapes,
                           MaterialContainer const& materials) const
    {
        return std::visit(
            [rec, &lights, &shapes, &materials](auto const& elem) {
                return elem.shade(rec, lights, shapes, materials);
            },
            m_material);
    }

private:
    std::variant<Materials...> m_material;
};

using Materials = MaterialWrapper<EmptyMaterial, Matte, Phong, Reflective>;
