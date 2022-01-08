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
        attenuation.constant = data.value("attenuation.constant", 0.0f);
        attenuation.linear = data.value("attenuation.linear", 0.0f);
        attenuation.quadratic = data.value("attenuation.quadratic", 1.0f);
        spot_angle.inner = glm::radians(data.value("spot_angle.inner", 90.0f));
        spot_angle.outer = glm::radians(data.value("spot_angle.outer", 180.0f));
    }

    glm::mat4 LightComponent::getLocalToWorldMatrix() const
    {
        return getOwner()->getLocalToWorldMatrix();
    }

    glm::mat4 LightComponent::getLocalToWorldMatrixInvTrans() const
    {
        glm::mat4 M = getLocalToWorldMatrix();
        return glm::inverse(glm::transpose(M));
    }

}