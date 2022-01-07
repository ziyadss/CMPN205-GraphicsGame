#include "light.hpp"

namespace our
{
    // Reads light parameters from the given json object
    void LightComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;
        std::string lightTypeStr = data.value("lightType", "directional");
        if (lightTypeStr == "point")
            lightType = LightType::POINT;
        else if (lightTypeStr == "spot")
            lightType = LightType::SPOT;
        else
            lightType = LightType::DIRECTIONAL;

        color = data.value("color", glm::vec3(1.0f, 1.0f, 1.0f));
        attenuation.constant = data.value("attenuation.constant", 0f);
        attenuation.linear = data.value("attenuation.linear", 0.0f);
        attenuation.quadratic = data.value("attenuation.quadratic", 1.0f);
        spot_angle.inner = data.value("spot_angle.inner", glm::pi<float>() / 4);
        spot_angle.outer = data.value("spot_angle.outer", glm::pi<float()> / 2);
    }
}