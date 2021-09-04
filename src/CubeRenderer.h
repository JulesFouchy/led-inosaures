#pragma once

#include <Cool/Camera/Camera.h>
#include <Cool/Gpu/OpenGL/Shader.h>

class CubeRenderer {
public:
    CubeRenderer();
    void render(const Cool::Camera& camera, const std::vector<glm::vec3>& colors) const;
    void imgui();

private:
    void upload_colors(const std::vector<glm::vec3>& _colors) const;

private:
    glm::vec3                    _scale{1.f};
    GLuint                       _vertex_buffer;
    GLuint                       _color_per_instance_buffer;
    GLuint                       _vertex_array;
    mutable Cool::OpenGL::Shader _shader{"shaders/leds.vert", "shaders/leds.frag"};

private:
    // Serialization
    friend class cereal::access;
    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("LED Size", _scale));
    }
};