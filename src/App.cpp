#include "App.h"
#include <Cool/Image/ImageSizeConstraintU.h>
#include <Cool/Log/ToUser.h>
#include <Cool/Serialization/JsonFile.h>
#include <Cool/Time/Time.h>

App::App(Window& mainWindow)
    : m_mainWindow(mainWindow)
{
    Serialization::from_json(*this, File::root_dir() + "/last-session-cache.json");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

App::~App()
{
    Serialization::to_json(*this, File::root_dir() + "/last-session-cache.json", "App");
}

void App::update()
{
    Time::update();
    ImageSizeConstraintU::apply(_preview_constraint, _render_target);
    render(_render_target, Time::time());
    _exporter.update({_render_target, [&](RenderTarget& render_target) {
                          render(render_target, Time::time());
                      }});
}

void App::render(RenderTarget& render_target, float time)
{
    _led_renderer.render(render_target, time);
}

void App::ImGuiWindows()
{
    ImGui::Begin("LED Renderer");
    _led_renderer.imgui();
    ImGui::End();
    //
    Log::ToUser::imgui_console_window();
    //
    ImGui::Begin("Time");
    Time::imgui_timeline();
    ImGui::End();
    //
    _render_target.imgui_window("1");
    _exporter.imgui_window_export_image({_render_target,
                                         [&](RenderTarget& render_target) { render(render_target, Time::time()); }});
    _exporter.imgui_window_export_image_sequence();
//
#if defined(DEBUG)
    if (m_bShow_Debug) {
        ImGui::Begin("Debug", &m_bShow_Debug);
        ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
        m_mainWindow.imgui_cap_framerate();
        ImGui::Checkbox("Show Demo Window", &m_bShow_ImGuiDemo);
        ImGui::End();
    }
    if (m_bShow_ImGuiDemo) // Show the big demo window (Most of the sample code is
                           // in ImGui::ShowDemoWindow()! You can browse its code
                           // to learn more about Dear ImGui!).
        ImGui::ShowDemoWindow(&m_bShow_ImGuiDemo);
#endif
}

void App::ImGuiMenus()
{
    if (ImGui::BeginMenu("Preview")) {
        _preview_constraint.imgui();
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Windows")) {
        Log::ToUser::imgui_toggle_console();
#ifndef NDEBUG
        ImGui::Separator();
        ImGui::Checkbox("Debug", &m_bShow_Debug);
#endif
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Export")) {
        _exporter.imgui_menu_items();
        ImGui::EndMenu();
    }
}

bool App::should_show_menu_bar()
{
    return !_exporter.is_exporting();
}

void App::onKeyboardEvent(int key, int scancode, int action, int mods)
{
    if (!_exporter.is_exporting() && !ImGui::GetIO().WantTextInput) {
    }
}

void App::onMouseButtonEvent(int button, int action, int mods)
{
    if (!_exporter.is_exporting() && !ImGui::GetIO().WantCaptureMouse) {
    }
}

void App::onScrollEvent(double xOffset, double yOffset)
{
    if (!_exporter.is_exporting() && !ImGui::GetIO().WantCaptureMouse) {
    }
}

void App::onMouseMoveEvent(double xpos, double ypos)
{
    if (!_exporter.is_exporting() && !ImGui::GetIO().WantCaptureMouse) {
    }
}