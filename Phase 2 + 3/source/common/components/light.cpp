#include "light.hpp"

namespace our
{
    // Reads light parameters from the given json object
    void LightComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;

        std::string light_type_str = data.value("lightType", "directional");

        if (light_type_str == "point")
            light_type = LightType::POINT;
        else if (light_type_str == "spot")
            light_type = LightType::SPOT;
        else
            light_type = LightType::DIRECTIONAL;

        enabled = data.value("enabled", true);
        color = data.value("color", glm::vec3(1.0f, 1.0f, 1.0f));

        attenuation.x = data.value("attenuation.constant", 0.0f);
        attenuation.y = data.value("attenuation.linear", 0.0f);
        attenuation.z = data.value("attenuation.quadratic", 1.0f);

        spot_angle.x = glm::radians(data.value("spot_angle.inner", 90.0f));
        spot_angle.y = glm::radians(data.value("spot_angle.outer", 180.0f));
    }

    // Reads sky light parameters from the given json object
    void SkyLightComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;

        sky = data.value("sky", glm::vec3(0.0f, 0.0f, 0.0f));
        horizon = data.value("horizon", glm::vec3(0.5f, 0.5f, 0.5f));
        ground = data.value("ground", glm::vec3(1.0f, 1.0f, 1.0f));
    }

}