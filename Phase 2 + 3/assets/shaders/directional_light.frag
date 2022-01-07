#version 330 core

#include "light_common.glsl"

in Varyings{
   vec4 color;
   vec2 tex_coord;
   vec3 normal;
}
fsin;

struct DirectionalLight{
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;

    vec3 direction; //directional lights defined only by a direciton and not a position (remove later --> get from entity)
};
//TO DO: FIX NORMALS AND VIEW 
uniform Material material;
uniform DirectionalLight light;

out vec4 frag_color;

void main(){
    vec3 diffuse = material.diffuse * light.diffuse * calculate_lambert(normal, light.direction);
    
    vec3 specular = material.specular * light.specular * calculate_phong(normal, light.direction, vec3(0.0f, 0.0f, -1.0f), material.shininess);
    
    vec3 ambient = material.ambient * light.ambient;
    
    frag_color = fsin.color * vec4(diffuse + specular + ambient, 1.0f);
}