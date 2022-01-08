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
    public:
        bool x = true;
        // This should be called every frame to update all entities containing a MovementComponent.
        void update(World *world, float deltaTime)
        {
            // For each entity in the world
            ColliderComponent *bullet = nullptr;
            ColliderComponent *cube = nullptr;
            Entity *Bullet = nullptr;
            // ColliderComponent *cube=nullptr;
            float raduisBullet = 0;
            float lengthCube = 0;
            glm::vec3 positionCube = {0, 0, 0};
            glm::vec3 centerBullet = {0, 0, 0};
            // cout<<"Collider update called"<<endl;
            for (auto entity : world->getEntities())
            {
                // Get the collider component if it exists
                ColliderComponent *collider = entity->getComponent<ColliderComponent>();

                // If the collider component exists
                if (collider && entity->name == "bullet")
                {
                    // cout<<"bullet collider found"<<endl;
                    bullet = collider;
                    Bullet = entity;
                    // centerBullet=collider->position +glm::vec3(entity->getLocalToWorldMatrix()*glm::vec4(0, 0, 0, 1));
                    // raduisBullet=collider->length * glm::length(entity->localTransform.scale)*1.7;
                    for (auto entity2 : world->getEntities())
                    {
                        // Get the collider component if it exists
                        ColliderComponent *collider2 = entity2->getComponent<ColliderComponent>();

                        // If the collider component exists
                        if (collider2 && entity2->name == "cube")
                        {
                            //  cout<<"plane collider found"<<endl;
                            cube = collider2;
                            // positionCube=collider->position +glm::vec3(entity->getLocalToWorldMatrix()*glm::vec4(0, 0, 0, 1));
                            // lengthCube=collider->length * glm::length(entity->localTransform.scale)*1.7;
                            if (checkCollision(bullet, collider2, Bullet, entity2))
                            {
                                // world->markForRemoval(entity);
                                MeshRendererComponent *Mesh = entity2->getComponent<MeshRendererComponent>();
                                Mesh->material = AssetLoader<Material>::get("white");
                            }
                        }
                    }
                }
            }

            world->deleteMarkedEntities();
        }
        bool checkCollision(ColliderComponent *bullet, ColliderComponent *cube, Entity *Bullet, Entity *Cube)
        {

            glm::vec3 centerBullet = bullet->position + glm::vec3(Bullet->getLocalToWorldMatrix() * glm::vec4(0, 0, 0, 1));

            float raduisBullet = bullet->length * glm::length(Bullet->localTransform.scale);

            glm::vec3 positionCube = cube->position + glm::vec3(Cube->getLocalToWorldMatrix() * glm::vec4(0, 0, 0, 1));

            glm::vec3 lengthCube = glm::vec3(cube->length, cube->length, cube->length) * Cube->localTransform.scale;
            glm::vec3 difference = centerBullet - positionCube;

            glm::vec3 clampedDifference = glm::clamp(difference, lengthCube * glm::vec3(-1.0f, -1.0f, -1.0f), lengthCube);

            glm::vec3 cubePoint = positionCube + clampedDifference;
            difference = cubePoint - centerBullet;
            return glm::length(difference) < raduisBullet;
        }
    };

}