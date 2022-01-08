#pragma once

#include "../ecs/world.hpp"
#include "../components/collider.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
namespace our
{

    class CollisionSystem
    {
        std::vector<ColliderComponent *> bullets, cubes;

    public:
        // This should be called every frame to update all entities containing a ColliderComponent.
        void update(World *world, float deltaTime)
        {
            bullets.clear();
            cubes.clear();

            for (const auto &entity : world->getEntities())
                if (auto bullet = entity->getComponent<ColliderComponent>(); bullet && entity->name == "bullet")
                    bullets.push_back(bullet);
                else if (auto cube = entity->getComponent<ColliderComponent>(); cube && entity->name == "cube")
                    cubes.push_back(cube);

            for (auto bullet : bullets)
                for (auto cube : cubes)
                    if (checkCollision(bullet, cube))
                        world->markForRemoval(cube->getOwner());

            world->deleteMarkedEntities();
        }

        bool checkCollision(ColliderComponent *bulletComponent, ColliderComponent *cubeComponent)
        {
            auto bullet = bulletComponent->getOwner();
            auto cube = cubeComponent->getOwner();

            glm::vec3 bulletCenter = bulletComponent->position + glm::vec3(bullet->getLocalToWorldMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
            glm::vec3 cubeCenter = cubeComponent->position + glm::vec3(cube->getLocalToWorldMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
            glm::vec3 cubeLength = glm::vec3(cubeComponent->length, cubeComponent->length, cubeComponent->length) * cube->localTransform.scale;

            glm::vec3 difference = bulletCenter - cubeCenter;
            glm::vec3 clampedDifference = glm::clamp(difference, cubeLength * glm::vec3(-1.0f, -1.0f, -1.0f), cubeLength);
            glm::vec3 cubePoint = cubeCenter + clampedDifference;

            difference = cubePoint - bulletCenter;
            float bulletRadius = bulletComponent->length * glm::length(bullet->localTransform.scale);
            return glm::length(difference) < bulletRadius;
        }
    };

}