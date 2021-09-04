#include "CubeRenderer.h"

CubeRenderer::CubeRenderer()
{
    glGenVertexArrays(1, &_vertex_array);
    glBindVertexArray(_vertex_array);
    GLfloat vertex_buffer_data[] = {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f};

    glGenBuffers(1, &_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
    glVertexAttribPointer(
        0,        // attribute
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void*)0  // array buffer offset
    );

    glGenBuffers(1, &_color_per_instance_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _color_per_instance_buffer);
}

void CubeRenderer::render(const Cool::Camera& camera, const std::vector<glm::vec3>& colors) const
{
    int nb_cubes = colors.size();
    _shader.bind();
    _shader.set_uniform("_proj_mat", camera.projection_matrix());
    _shader.set_uniform("_view_mat", camera.view_matrix());
    _shader.set_uniform("_nb_instances", nb_cubes);
    _shader.set_uniform("_scale", 0.05f * _scale);
    glBindVertexArray(_vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
    upload_colors(colors);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, nb_cubes);
}

void CubeRenderer::upload_colors(const std::vector<glm::vec3>& colors) const
{
    glBindBuffer(GL_ARRAY_BUFFER, _color_per_instance_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colors.size(), reinterpret_cast<const float*>(colors.data()), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _color_per_instance_buffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(1, 1);
}

void CubeRenderer::imgui()
{
    ImGui::SliderFloat3("LED Size", glm::value_ptr(_scale), 0.f, 10.f);
}