#pragma once

#include "../ecs/world.hpp"
#include "../components/collider.hpp"
#include "../components/movement.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
namespace our
{

    class CollisionSystem
    {
        std::vector<ColliderComponent *> bullets, cubes, walls;

    public:
        // This should be called every frame to update all entities containing a ColliderComponent.


        void checkCollisioncolor(ColliderComponent bullet, ColliderComponent cube)
        {
            //this function checks that the color of the bullet compnent and the collider component
            //match the necessary logic (i.e are complimentary, or pseudo complimentary for testing)
            
        }
        void update(World *world, float deltaTime)
        {
            bullets.clear();
            cubes.clear();
            walls.clear();

            for (const auto &entity : world->getEntities())
                if (auto bullet = entity->getComponent<ColliderComponent>(); bullet && entity->name == "bullet")
                    bullets.push_back(bullet);
                else if (auto cube = entity->getComponent<ColliderComponent>(); cube && entity->name == "cube")
                    cubes.push_back(cube);
                else if (auto wall = entity->getComponent<ColliderComponent>(); wall && entity->name == "wall")
                    walls.push_back(wall);

            for (auto bullet : bullets)
            {
                for (auto cube : cubes)
                    if (checkCollision(bullet, cube))
                    {
                        // world->markForRemoval(cube->getOwner());
                        MeshRendererComponent *Mesh = cube->getOwner()->getComponent<MeshRendererComponent>();

                        //this should check the color of the colliders first
                        //(bad implementation) iterate through all assets -->  
                        if (bullet->getOwner()->getComponent<MeshRendererComponent>()->material == cube->getOwner()->getComponent<MeshRendererComponent>()->material)
                            checkCollionColor(cube, bullet);
                        MovementComponent *movement = bullet->getOwner()->getComponent<MovementComponent>();
                        movement->linearVelocity = {0, 0, 0};
                        bullet->getOwner()->localTransform.position = {1, -1, -1};
                    }
                for (auto wall : walls)
                    if (checkCollision(bullet, wall))
                    {
                        MovementComponent *movement = bullet->getOwner()->getComponent<MovementComponent>();
                        movement->linearVelocity = {0, 0, 0};
                        bullet->getOwner()->localTransform.position = {1, -1, -1};
                    }
                glm::vec3 bulletCenter = bullet->position + glm::vec3(bullet->getOwner()->getLocalToWorldMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
                if (bulletCenter.x > 11 || bulletCenter.x < -11 || bulletCenter.y > 11 || bulletCenter.y < -11 || bulletCenter.z > 11 || bulletCenter.z < -11)
                {
                    MovementComponent *movement = bullet->getOwner()->getComponent<MovementComponent>();
                    movement->linearVelocity = {0, 0, 0};
                    bullet->getOwner()->localTransform.position = {1, -1, -1};
                }
            }

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