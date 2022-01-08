#include "collider.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our
{
    // Reads linearVelocity & angularVelocity from the given json object
    void ColliderComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;
        position = data.value("position", position);
        length = data.value("length", length);
    }
}