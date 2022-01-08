#version 330 core

#define DIRECTIONAL 0
#define POINT 1
#define SPOT 2

in Varyings {
    vec4 color;
    vec2 tex_coord;
    vec3 normal;
    vec3 world;
    vec3 view;
} fs_in;

struct Material {
    vec3 diffuse, specular, ambient, emissive;
    float shininess;
};

struct LitMaterial {
    sampler2D albedo_map, specular_map, ambient_occlusion_map, roughness_map, emissive_map;
    vec3 albedo_tint, specular_tint, emissive_tint;
    vec2 roughness_range;
};

Material sample_material(LitMaterial tex_mat, vec2 tex_coord) {
    Material mat;

    mat.diffuse = texture(tex_mat.albedo_map, tex_coord).rgb * tex_mat.albedo_tint;
    mat.specular = texture(tex_mat.specular_map, tex_coord).rgb * tex_mat.specular_tint;
    mat.ambient = texture(tex_mat.ambient_occlusion_map, tex_coord).rgb * mat.diffuse;
    mat.emissive = texture(tex_mat.emissive_map, tex_coord).rgb * tex_mat.emissive_tint;
    
    float roughness = mix(tex_mat.roughness_range.x, tex_mat.roughness_range.y, texture(tex_mat.roughness_map, tex_coord).r);

    mat.shininess = 2.0f / pow(clamp(roughness, 0.001f, 0.999f), 4.0f) - 2.0f;

    return mat;
}

struct Light {
    int type;
    vec3 color;
    vec3 position, direction;
    
    vec3 attenuation; // constant, linear, quadratic
    
    vec2 spot_angle; // inner, outer
};

struct SkyLight {
    vec3 sky, horizon, ground;
};

float calculate_lambert(vec3 normal, vec3 light_direction){
    return max(dot(normal, -light_direction), 0.0f);
}

float calculate_phong(vec3 normal, vec3 light_direction, vec3 view, float shininess){
    vec3 reflected = reflect(light_direction, normal);
    return pow(max(dot(view, reflected), 0.0f), shininess);
}


#define MAX_LIGHTS 16

uniform LitMaterial material;
uniform int light_count;
uniform Light lights[MAX_LIGHTS];
uniform SkyLight sky_light;

out vec4 frag_color;

void main(){

    Material sampled = sample_material(material, fs_in.tex_coord);

    vec3 normal = normalize(fs_in.normal);
    vec3 view = normalize(fs_in.view);

    vec3 ambient = sampled.ambient * (normal.y > 0 ? mix(sky_light.sky, sky_light.horizon, normal.y) : mix(sky_light.horizon, sky_light.ground, -normal.y));

    vec3 accumulated_light = sampled.emissive + ambient;

    int count = min(MAX_LIGHTS, light_count);

    for (int i = 0; i < count; i++)
    {
        Light light = lights[i];
        vec3 light_direction;
        float attenuation = 1;
        
        if (light.type == DIRECTIONAL)
            light_direction = light.direction;
        else
        {
            light_direction = fs_in.world - light.position;
            float distance = length(light_direction);
            light_direction = normalize(light_direction);

            attenuation = 1.0f / (light.attenuation.x + light.attenuation.y * distance + light.attenuation.z * distance * distance);

            if (light.type == SPOT)
                attenuation *= smoothstep(light.spot_angle.x, light.spot_angle.y, acos(dot(light_direction, light.direction)));
        }

        vec3 diffuse = sampled.diffuse * light.color * calculate_lambert(normal, light_direction);
        vec3 specular = sampled.specular * light.color * calculate_phong(normal, light_direction, view, sampled.shininess);

        accumulated_light += (diffuse + specular) * attenuation;
    }

    frag_color = fs_in.color * vec4(accumulated_light, 1.0f);
}