#include "material.hpp"

#include "../asset-loader.hpp"
#include "deserialize-utils.hpp"

namespace our
{

    // This function should setup the pipeline state and set the shader to be used
    void Material::setup() const
    {
        pipelineState.setup();
        shader->use();
    }

    // This function read the material data from a json object
    void Material::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;

        if (data.contains("pipelineState"))
            pipelineState.deserialize(data["pipelineState"]);

        shader = AssetLoader<ShaderProgram>::get(data["shader"].get<std::string>());
        transparent = data.value("transparent", false);
    }

    // This function should call the setup of its parent and
    // set the "tint" uniform to the value in the member variable tint
    void TintedMaterial::setup() const
    {
        Material::setup();
        
        shader->set("tint", tint);
    }

    // This function read the material data from a json object
    void TintedMaterial::deserialize(const nlohmann::json &data)
    {
        Material::deserialize(data);

        if (!data.is_object())
            return;

        tint = data.value("tint", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    // This function should call the setup of its parent and
    // set the "alphaThreshold" uniform to the value in the member variable alphaThreshold
    // Then it should bind the texture and sampler to a texture unit and send the unit number to the uniform variable "tex"
    void TexturedMaterial::setup() const
    {
        TintedMaterial::setup();

        shader->set("alphaThreshold", alphaThreshold);

        glActiveTexture(GL_TEXTURE0);
        texture->bind();
        sampler->bind(0);
        shader->set("tex", 0);
    }

    // This function read the material data from a json object
    void TexturedMaterial::deserialize(const nlohmann::json &data)
    {
        TintedMaterial::deserialize(data);
        if (!data.is_object())
            return;

        alphaThreshold = data.value("alphaThreshold", 0.0f);
        texture = AssetLoader<Texture2D>::get(data.value("texture", ""));
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
    }

    // This function should call the setup of its parent and
    // set the "diffuse", "specular" and "ambient" uniforms to the value in the member variables
    void LitMaterial::setup() const
    {
        Material::setup();

        glActiveTexture(GL_TEXTURE1);
        albedo_map->bind();
        sampler->bind(1);
        shader->set("material.albedo_map", 1);
        shader->set("material.albedo_tint", albedo_tint);

        glActiveTexture(GL_TEXTURE2);
        specular_map->bind();
        sampler->bind(2);
        shader->set("material.specular_map", 2);
        shader->set("material.specular_tint", specular_tint);

        glActiveTexture(GL_TEXTURE3);
        roughness_map->bind();
        sampler->bind(3);
        shader->set("material.roughness_map", 3);

        glActiveTexture(GL_TEXTURE4);
        ambient_occlusion_map->bind();
        sampler->bind(4);
        shader->set("material.ambient_occlusion_map", 4);

        if (emissive_map)
        {
            glActiveTexture(GL_TEXTURE5);
            emissive_map->bind();
            sampler->bind(5);
            shader->set("material.emissive_map", 5);
            shader->set("material.emissive_tint", emissive_tint);
        }

        shader->set("roughness_range", roughness_range);
    }

    // This function read the material data from a json object
    void LitMaterial::deserialize(const nlohmann::json &data)
    {
        Material::deserialize(data);

        if (!data.is_object())
            return;

        albedo_map = AssetLoader<Texture2D>::get(data.value("albedo_map", ""));
        specular_map = AssetLoader<Texture2D>::get(data.value("specular_map", ""));
        roughness_map = AssetLoader<Texture2D>::get(data.value("roughness_map", ""));
        ambient_occlusion_map = AssetLoader<Texture2D>::get(data.value("ambient_occlusion_map", ""));
        emissive_map = AssetLoader<Texture2D>::get(data.value("emissive_map", ""));

        albedo_tint = data.value("albedo_tint", glm::vec3(1.0f, 1.0f, 1.0f));
        specular_tint = data.value("specular_tint", glm::vec3(1.0f, 1.0f, 1.0f));
        emissive_tint = data.value("emissive_tint", glm::vec3(1.0f, 1.0f, 1.0f));

        roughness_range = data.value("roughness_range", glm::vec2(0.0f, 1.0f));

        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
    }

}