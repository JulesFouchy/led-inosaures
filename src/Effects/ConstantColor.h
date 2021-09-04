#pragma once
#include "../MyMath.h"

class ConstantColor {
public:
    void apply(std::vector<glm::vec3>& colors, float time /* in seconds */)
    {
        for (auto i = 0; i < colors.size(); ++i) {
            colors[i] = _color;
        }
    }

    void imgui() // Displays some UI to control the effect ; this is very usefull to quickly find values that look good !
    {
        ImGui::ColorEdit3("Color", glm::value_ptr(_color), ImGuiColorEditFlags_NoInputs);
    }

private:
    glm::vec3 _color{1.f};

private:
    // Serialization. This allows us to save your current settings and restore them when you close and re-open the application !
    friend class cereal::access;
    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(
            _color
            /* you can add more member variables here */);
    }
};
