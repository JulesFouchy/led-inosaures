#version 330 core

layout(location = 0) in vec3 _vertex_position;
layout(location = 1) in vec3 _instance_color;
uniform mat4 _proj_mat;
uniform mat4 _view_mat;
uniform int  _nb_instances;
uniform vec3 _scale;

out vec3 _led_color;

void main()
{
    // clang-format off
    gl_Position = _proj_mat * _view_mat * vec4(
        _scale * (_vertex_position + vec3(0., (gl_InstanceID - _nb_instances / 2) * 3., 0.))
        , 1.0);
    _led_color = _instance_color;
    // clang-format on
}