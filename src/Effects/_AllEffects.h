#pragma once
class CurrentEffect;
template<typename T>
void register_effect(std::string_view name, CurrentEffect& e);

// ****************************************
// *----- REGISTER YOUR EFFECTS HERE -----*
// ****************************************

// STEP 1
#include "ConstantColor.h"
#include "Gradient.h"

// STEP 2
using Effect = std::variant<
    Gradient,
    ConstantColor>;

// STEP 3
inline void RegisterEffects(CurrentEffect& e)
{
    register_effect<Gradient>("Gradient", e);
    register_effect<ConstantColor>("Constant Color", e);
}

// ********************************************************
// *----- YOU DON'T NEED TO CARE ABOUT WHAT IS BELOW -----*
// ********************************************************

class CurrentEffect {
public:
    void apply(std::vector<glm::vec3>& colors, float time)
    {
        make_sure_it_is_initialized();
        std::visit([&](auto&& effect) { effect.apply(colors, time); }, current_effect());
    }

    void imgui()
    {
        make_sure_it_is_initialized();
        ImGui::Combo("Effect", &_current_effect_idx, _effects_names_list.c_str());
        std::visit([&](auto&& effect) { effect.imgui(); }, current_effect());
    }

    template<typename T>
    void register_effect(std::string_view name)
    {
        _effects_names_list += name;
        _effects_names_list += '\0';
        if (std::none_of(_effects.begin(), _effects.end(), [&](Effect& e) { return std::get_if<T>(&e) != nullptr; })) {
            _effects.push_back(T{});
        }
    }

    Effect& current_effect() { return _effects[_current_effect_idx]; }

    void make_sure_it_is_initialized()
    {
        if (_must_initialize) {
            RegisterEffects(*this);
            _must_initialize = false;
        }
    }

private:
    std::vector<Effect> _effects;
    std::string         _effects_names_list = "";
    int                 _current_effect_idx = 0;
    bool                _must_initialize    = true;

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
void register_effect(std::string_view name, CurrentEffect& e)
{
    e.register_effect<T>(name);
}