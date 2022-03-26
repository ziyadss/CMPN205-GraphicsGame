#version 330 core

layout(location = 0) in vec3 position;

out Varyings {
    vec3 view;
} vs_out;

uniform mat4 VP;
uniform vec3 camera_position;


void main() {
    vs_out.view = position;
    
    vec4 clip_space = VP * vec4(position + camera_position, 1.0f);

    gl_Position = clip_space.xyww;
}