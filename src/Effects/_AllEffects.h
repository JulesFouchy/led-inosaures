#pragma once
template<typename T>
void register_effect(std::string_view name);

// ****************************************
// *----- REGISTER YOUR EFFECTS HERE -----*
// ****************************************

#include "ConstantColor.h"
#include "Gradient.h"

using Effect = std::variant<
    Gradient,
    ConstantColor>;

inline void RegisterEffects()
{
    register_effect<Gradient>("Gradient");
    register_effect<ConstantColor>("Constant Color");
}

// ********************************************************
// *----- YOU DON'T NEED TO CARE ABOUT WHAT IS BELOW -----*
// ********************************************************

class CurrentEffect {
public:
    void apply(std::vector<glm::vec3>& colors, float time)
    {
        std::visit([&](auto&& effect) { effect.apply(colors, time); }, current_effect());
    }

    void imgui()
    {
        ImGui::Combo("Effect", &_current_effect_idx, _effects_names_list.c_str());
        std::visit([&](auto&& effect) { effect.imgui(); }, current_effect());
    }

    static CurrentEffect& instance()
    {
        static CurrentEffect my_instance{};
        return my_instance;
    }

    template<typename T>
    void register_effect(std::string_view name)
    {
        _effects.push_back(T{});
        _effects_names_list += name;
        _effects_names_list += '\0';
    }

    Effect& current_effect() { return _effects[_current_effect_idx]; }

private:
    std::vector<Effect> _effects;
    std::string         _effects_names_list = "";
    int                 _current_effect_idx = 0;

private:
    // Serialization
    friend class cereal::access;
    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("Effects", _effects),
            cereal::make_nvp("Current effect index", _current_effect_idx));
    }
};

template<typename T>
void register_effect(std::string_view name)
{
    CurrentEffect::instance().register_effect<T>(name);
}