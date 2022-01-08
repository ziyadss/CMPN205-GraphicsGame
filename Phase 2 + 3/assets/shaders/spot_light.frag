#version 330 core

#include "light_common.glsl"


in varyings{
    vec4 color;
    vec2 tex_coord;
    ///////WARNING
    vec3 normal;
    vec3 view;
} fsin;


uniform Material material;
uniform LightComponent light;

out vec4 frag_color;

void main(){

    vec3 normal = normalize(fsin.normal);
    //normal may become shorter during interpolation
    vec3 view = vec3(0.0f, 0.0f, -1.0f);
    
    vec3 light_direction = fsin.world - light.position;

    float distance = length(light_direction);
    light_direction /= distnace;

    //calculating attentuation factor:

    float attentuation = 1.0f / (light.attenuation.constant + light.attenuation.linear * distance + light.attenuation.quadratic * distance * distance);

    float angle = acos(dot(light.direction, light_direction));
    //look @ this again

    float angle_attenuation = smoothstep(light.spot_angle.outer, light.spot_angle.inner, angle);


    vec3 diffuse = material.diffuse * light.diffuse * calculate_lambert(normal, light_direction);
    vec3 specular = material.specular * light.specular * calculate_phong(normal, light_direction, view, material.shininess);
    vec3 ambient = material.ambient * light.ambient;

    //combine light components
    //attenuation only affects diffuse and specular, ambient is constant regardless of light and position.
    frag_color = fsin.color * vec4((diffuse + specular) * attentuation * angle_attenuation + ambient, 1.0f);
}