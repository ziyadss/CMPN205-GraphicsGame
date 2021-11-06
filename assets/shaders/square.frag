#version 330 core

out vec4 frag_color;

//TODO: Define uniforms for the center and the side-length
uniform float side_length;
uniform vec2 center;

uniform vec4 inside_color = vec4(1.0, 0.0, 0.0, 1.0);
uniform vec4 outside_color = vec4(0.0, 0.0, 0.0, 1.0);

void main()
{
    float x = gl_FragCoord.x;
    float y = gl_FragCoord.y;
    float x_c = center.x;
    float y_c = center.y;
    if (max(abs(x - x_c), abs(y - y_c)) <= 0.5 * side_length){
        frag_color = inside_color;
    } else {
        frag_color = outside_color;
    }
}