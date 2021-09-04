#include "LedRenderer.h"

LedRenderer::LedRenderer()
{
    _view_controller.on_wheel_down(_camera, 0);
    _view_controller.on_mouse_move(_camera, {0.1f, 3.f});
    _view_controller.on_wheel_up(_camera);
}

void LedRenderer::render(Cool::RenderTarget& render_target, float time)
{
    _leds_colors.resize(_nb_leds);
    _current_effect.apply(_leds_colors, time);
    _proj_controller.apply_to(_camera, render_target.info().viewport.aspectRatio());
    render_target.render([&]() {
        glClearColor(_background_color.r,
                     _background_color.g,
                     _background_color.b,
                     1.);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _cube_renderer.render(_camera, _leds_colors);
    });
}

void LedRenderer::imgui()
{
    ImGui::ColorEdit3("Background", glm::value_ptr(_background_color), ImGuiColorEditFlags_NoInputs);
    _cube_renderer.imgui();
    ImGui::Separator();
    _current_effect.imgui();
}