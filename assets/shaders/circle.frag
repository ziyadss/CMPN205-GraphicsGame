#version 330 core

out vec4 frag_color;

uniform vec2 center = vec2(256, 256);
uniform float radius = 128;

uniform vec4 inside_color = vec4(1.0, 0.0, 0.0, 1.0);
uniform vec4 outside_color = vec4(0.0, 0.0, 0.0, 1.0);

void main()
{
    const vec2 vector = gl_FragCoord.xy - center;
    const float euclideanDistance = length(vector);

    // If distance is less than or equal to radius, set color to inside color
    frag_color = (euclideanDistance <= radius) ? inside_color : outside_color;
}