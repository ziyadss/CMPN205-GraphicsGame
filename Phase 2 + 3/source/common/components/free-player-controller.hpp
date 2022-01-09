#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our
{

    class FreePlayerControllerComponent : public Component
    {
    public:
        // The senstivity paramter defined sensitive the camera rotation & fov is to the mouse moves and wheel scrolling
        float bulletSpeed = 0.0f;               
        
        // The ID of this component type is "Free Camera Controller"
        static std::string getID() { return "Free player Controller"; }

        // Reads sensitivities & speedupFactor from the given json object
        void deserialize(const nlohmann::json &data) override;
    };

}