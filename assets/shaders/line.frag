#version 330 core

out vec4 frag_color;

uniform vec4 inside_color = vec4(1.0, 0.0, 0.0, 1.0);
uniform vec4 outside_color = vec4(0.0, 0.0, 0.0, 1.0);
uniform float intercept = 0;
uniform float slope = 1.0;

void main()
{
    float y_coordinate = slope * gl_FragCoord.x + intercept;
    if (gl_FragCoord.y <= y_coordinate)
        frag_color = inside_color;
    else
        frag_color = outside_color;
}