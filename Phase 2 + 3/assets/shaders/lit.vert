#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 normal;

out Varyings
{
    vec4 color;
    vec2 tex_coord;
    vec3 normal;
    vec3 world;
    vec3 view;
} vs_out;

uniform mat4 local_to_world;
uniform mat4 VP;
uniform vec3 camera_position;

void main()
{
    vs_out.color = color;
    vs_out.tex_coord = tex_coord;
    vs_out.normal = normalize(transpose(inverse(local_to_world)) * vec4(normal, 0.0f)).xyz;
    
    vs_out.world = (local_to_world * vec4(position, 1.0f)).xyz;
    gl_Position = VP * vec4(vs_out.world, 1.0f);

    vs_out.view = normalize(camera_position - vs_out.world);
}