#pragma once

#include "shapes.hpp"

template<typename T>
class Material : public utils::StaticBase<T, Material>
{
public:
    constexpr Colourf shade(ShadeRec const& rec) const
    {
        return this->self().shade(rec);
    }
};

class DefaultMaterial : public Material<DefaultMaterial>
{
public:
    constexpr Colourf shade([[maybe_unused]] ShadeRec const& rec) const
    {
        return {1.0f, 0.0f, 0.0f};
    }
};

template<class... Materials>
class MaterialWrapper
{
public:
    template<typename T, typename = utils::Contains<T, Materials...>>
    constexpr MaterialWrapper(T&& elem) : m_materials{std::forward<T>(elem)}
    {}

    constexpr Colourf shade(ShadeRec const& rec) const
    {
        return std::visit([rec](auto const& elem) { return elem.shade(rec); },
                          m_materials);
    }

private:
    std::variant<Materials...> m_materials;
};

using Materials = MaterialWrapper<DefaultMaterial>;

template<typename Container>
class MaterialContainer
{
public:
    constexpr MaterialContainer(Container&& list) :
        m_materials{std::forward<Container>(list)}
    {}

    constexpr auto& operator[](int material_id)
    {
        return m_materials[material_id];
    }

    constexpr auto operator[](int material_id) const
    {
        return m_materials[material_id];
    }

private:
    Container m_materials;
};
