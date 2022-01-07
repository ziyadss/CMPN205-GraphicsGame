#version 330 core


#define DIRECTIONAL 0
#define POINT 1
#define SPOT 2

in Varyings {
    vec3 normal;
    vec3 view;
    vec3 world;
    vec3 tex_coord;
} fs_in;

out vec4 frag_color;

struct Material{
    sampler2D albedo;
    sampler2D specular;
    sampler2D roughness;
    sampler2D ambient_occlusion;
    sampler2D emission;
};

struct Light {
    int type;
    vec3 position;
    vec3 direction;
    vec3 color;
    vec3 attenuation;
    vec2 cone_angles;
};

struct SkyLight {
    vec3 sky, horizon, ground;
};

float lambert(vec3 n, vec3 l)
{
    return max(dot(n, l), 0.0);
}

float phong(vec3 n, vec3 l, vec3 v, float shininess){
    vec3 r = reflect(-l, n);
    return pow(max(0, dov(v, r)), shininess);
}

vec3 compute_sky_light(vec3 normal, SkyLight, sky_light){
        float y = normal.y;
        float sky_factor = max(0, y);
        float ground_factor = max(0, -y);
        sky_factor *= sky_factor;
        ground_factor *= ground_factor;
        float horizon_factor = 1 - sky_factor - ground.factor;
        return sky_light>sky * sky_factor + sky_light.horizon * horizon_factor + sky_light.ground * ground_factor;
}


uniform Material material;
uniform int light_count;
uniform Light lights[MAX_LIGHTS];
uniform SkyLight sky_light;
uniform MAX_LIGHTS;

void main(){
    vec3 normal = normalize(fs_in.normal);
    vec3 view = normalize(fs_in.view);

    vec3 material_albedo = texture(material.albedo, fs_in.tex_coord).rgb;
    vec3 material_specular = texture(material.specular, fs_in.tex_coord).rgb;
    float roughness = texture(material.roughness, fs_in.tex_coord).r;
    float shininess = 2.0f/pow(clamp(roughness, 0.001f, 0.999f), 4.0f) - 2.0f;
    vec3 material_emission = texture(material.emission, fs_in.tex_coord).rgb;
    float material_ao = texture(material.ambient_occlusion, fs_in.tex_coord).r;

    frag_color = vec4(material_emission + material_albedo * material_ao * compute_sky_light(normal, sky_light), 1);

    for (int i = 0; i < min(MAX_LIGHTS, light_count); ++i){
        Light light = lights[i];

        vec3 light.vec = -light.direction;
        if(light.type != DIRECTIONAL){
            light_vec = normalize(light.position - fs_in.world);
        }

        vec3 diffuse = material_albedo * light.color * lambert(normal, light_vec);
        vec3 specular = material_specular * light.color * phong(normal, light_vec, view, shininess);

        float attenuation = 1;
        if (light.type != DIRECTIONAL){
            float d = distance(light.position, fs_in.world);
            attenuation *= 1.0/dot(light.attenuation, vec3(1, d, d*d));
            if(light.type == SPOT){
                float angle = acos(-dot(light.direction, light_vec));
                attenuation *= smoothstep(light.cone_angles.y, light.cone_angles.x, angle);
            }
        }
        frag_color.rgb += (diffuse + specular) * attenuation;
    }
}