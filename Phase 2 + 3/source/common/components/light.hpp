#pragma once

#include "mesh-renderer.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "../ecs/entity.hpp"
#include "deserialize-utils.hpp"

namespace our
{
    // An enum that defines the type of the light (DIRECTIONAL, POINT or SPOT)
    enum class LightType
    {
        DIRECTIONAL,
        POINT,
        SPOT
    };

    class LightComponent : public Component
    {
    public:
        LightType light_type; // The type of the light
        bool enabled;         // Whether the light is enabled or not
        glm::vec3 color;      // The color of the light

        glm::vec3 attenuation; // constant, linear, quadratic

        glm::vec2 spot_angle; // inner, outer

        // The ID of this component type is "Light"
        static std::string getID() { return "Light"; }

        // Reads light parameters from the given json object
        void deserialize(const nlohmann::json &data) override;
    };

    class SkyLightComponent : public MeshRendererComponent
    {
    public:
        glm::vec3 sky, horizon, ground;

        // The ID of this component type is "SkyLight"
        static std::string getID() { return "SkyLight"; }

        // Reads sky light parameters from the given json object
        void deserialize(const nlohmann::json &data) override;
    };
}