#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our
{

    class FreePlayerControllerComponent : public Component
    {
    public:
        // The player's bullet speed
        float bulletSpeed = 0.0f;

        // The ID of this component type is "Free Player Controller"
        static std::string getID() { return "Free Player Controller"; }

        void deserialize(const nlohmann::json &data) override;
    };

}