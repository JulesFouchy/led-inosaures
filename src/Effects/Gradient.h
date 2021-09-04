#pragma once

class Gradient {
public:
    void apply(std::vector<glm::vec3>& colors, float time /* in seconds */)
    {
        for (auto i = 0; i < colors.size(); ++i) {
            float t   = static_cast<float>(i) / static_cast<float>(colors.size() - 1);
            colors[i] = glm::vec3{t + time};
        }
    }

    void imgui(){};
};
