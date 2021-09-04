#pragma once
#include "../Math.h"

class Gradient {
public:
    void apply(std::vector<glm::vec3>& colors, float time /* in seconds */)
    {
        for (auto i = 0; i < colors.size(); ++i) {
            float t   = static_cast<float>(i) / static_cast<float>(colors.size() - 1);
            colors[i] = glm::vec3{fract(t + time)};
        }
    }
    void imgui() // Displays some UI to control the effect ; this is very usefull to quickly find values that look good !
    {
    }

private:
    // Serialization. This allows us to save your current settings and restore them when you close and re-open the application !
    friend class cereal::access;
    template<class Archive>
    void serialize(Archive& archive)
    {
        // archive(
        //     /* you can add more member variables here */);
    }
};
