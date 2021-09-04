#version 450

layout(location = 0) out vec4 _out_color;
in vec3 _led_color;

void main()
{
    _out_color = vec4(pow(_led_color, vec3(0.4545)), 1.);
}
