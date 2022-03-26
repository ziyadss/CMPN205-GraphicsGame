#version 330 core

in Varyings {
    vec3 view;
} fs_in;

struct SkyLight {
    vec3 sky, horizon, ground;
};

uniform SkyLight sky_light;
uniform float exposure;

out vec4 frag_color;

void main(){
    
    vec3 view = normalize(fs_in.view);

    vec3 sky_color = exposure * (view.y > 0 ?
    mix(sky_light.horizon, sky_light.sky, view.y) :
    mix(sky_light.horizon, sky_light.ground, -view.y));

    frag_color = vec4(sky_color, 1.0f);
}
