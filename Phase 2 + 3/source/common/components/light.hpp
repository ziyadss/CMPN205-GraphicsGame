#pragma once

#include "../ecs/component.hpp"

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
        LightType lightType; // The type of the light
        glm::vec3 color;     // The color of the light
        // What else? 'cone angles'?

        struct
        {
            float constant, linear, quadratic;
        } attenuation;

        struct 
        {
            float inner, outer;
        } spot_angle;
        // The ID of this component type is "Light"
        static std::string getID() { return "Light"; }

        // Reads light parameters from the given json object
        void deserialize(const nlohmann::json &data) override;
    };
}