#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 tex_coord;

/*
    -an object to world transformation (this is provided by entity)
    -an object to world inverse transpose (for normals)
    -a world to homogenous clipspace
    -and a camera position,
*/
out Varyings{
    vec4 color;
    vec2 tex_coord;

    vec3 normal; 
} vs_out;

uniform mat4 transform; //this is the position of the light source
//view vector is known (0,0,-1)
uniform LightComponent light;
void main(){
    
    gl_Position = transform * vec4(position, 1.0);
    vs_out.color = color; 
    vs_out.tex_coord = tex_coord; 
}