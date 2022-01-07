#version 330 core

out vec4 frag_color;

uniform vec2 center = vec2(256, 256);
uniform float side_length = 128;

uniform vec4 inside_color = vec4(1.0, 0.0, 0.0, 1.0);
uniform vec4 outside_color = vec4(0.0, 0.0, 0.0, 1.0);

void main()
{
    vec2 vector = gl_FragCoord.xy - center;
    float taxicabDistance = abs(vector.x) + abs(vector.y);

    // If taxicab distance is less than or equal to half the side length, set color to inside color
    frag_color = (taxicabDistance <= side_length / 2) ? inside_color : outside_color;
}