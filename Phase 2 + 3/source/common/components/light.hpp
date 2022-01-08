#pragma once

#include "../ecs/component.hpp"
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
        LightType lightType; // The type of the light
        glm::vec3 color;     // The color of the light
        glm::mat4 LocalToWorldInvTrans;

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

        glm::mat4 getLocalToWorldMatrix() const;
        glm::mat4 getLocalToWorldMatrixInvTrans() const;
    };
}