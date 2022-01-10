#include "free-player-controller.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our
{
    void FreePlayerControllerComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;

        bulletSpeed = data.value("bulletSpeed", bulletSpeed);
    }
}