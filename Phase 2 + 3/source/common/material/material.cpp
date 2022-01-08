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
        shader->set("diffuse", diffuse);
        shader->set("specular", specular);
        shader->set("ambient", ambient);
    }

    // This function read the material data from a json object
    void LitMaterial::deserialize(const nlohmann::json &data)
    {
        Material::deserialize(data);
        if (!data.is_object())
            return;

        diffuse = data.value("diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
        specular = data.value("specular", glm::vec3(0.0f, 0.0f, 0.0f));
        ambient = data.value("ambient", glm::vec3(0.0f, 0.0f, 0.0f));
        shininess = data.value("shininess", 1.0f);
        roughness = data.value("roughness", 0.0f);
        ambient_occlusion = data.value("ambient_occlusion", 0.0f);
        emission = data.value("emission", 0.0f);
    }

}