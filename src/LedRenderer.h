#pragma once

#include <Cool/Camera/Camera.h>
#include <Cool/Camera/ProjectionController_Perspective.h>
#include <Cool/Camera/ViewController_Orbital.h>
#include <Cool/Gpu/RenderTarget.h>
#include "CubeRenderer.h"

class LedRenderer {
public:
    LedRenderer();
    void render(Cool::RenderTarget& render_target, float time);
    void imgui();

private:
    int                                    _nb_leds          = 30;
    glm::vec3                              _background_color = glm::vec3(0.f, 0.f, 0.f);
    Cool::Camera                           _camera;
    Cool::ProjectionController_Perspective _proj_controller;
    Cool::ViewController_Orbital           _view_controller;
    CubeRenderer                           _cube_renderer;
    std::vector<glm::vec3>                 _leds_colors;

private:
    // Serialization
    friend class cereal::access;
    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("Background color", _background_color),
            cereal::make_nvp("Number of LEDs", _nb_leds),
            cereal::make_nvp("LEDS", _cube_renderer));
    }
};