#pragma once
#include "../ecs/world.hpp"
#include "../components/free-player-controller.hpp"

#include "../components/movement.hpp"
#include "../components/mesh-renderer.hpp"

#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace our
{

    // The free camera controller system is responsible for moving every entity which contains a FreeCameraControllerComponent.
    // This system is added as a slightly complex example for how use the ECS framework to implement logic.
    // For more information, see "common/components/free-camera-controller.hpp"
    class FreePlayerControllerSystem
    {
        Application *app;     // The application in which the state runs
        float wait = 0.0f;       // time to wait for keypresses
        float interval = 0.05f; // time taken before reading another key
    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
        }
        int color = 0; // 0-> red, 1->blue, 2->green
        // This should be called every frame to update all entities containing a FreeCameraControllerComponent
        void update(World *world, float deltaTime)
        {
            FreePlayerControllerComponent *controller = nullptr;
            Entity *bullet = nullptr;
            // First of all, we search for an entity containing both a CameraComponent and a FreeCameraControllerComponent
            // As soon as we find one, we break
            for (auto entity : world->getEntities())
            {
                controller = entity->getComponent<FreePlayerControllerComponent>();
                if (entity->name == "bullet")
                    bullet = entity;
                if (controller && bullet)
                    break;
            }
            // If there is no entity with both a CameraComponent and a FreeCameraControllerComponent, we can do nothing so we return
            if (!controller || !bullet)
                return;
            // Get the entity that we found via getOwner of camera (we could use controller->getOwner())
            Entity *player = controller->getOwner();

            // We change the camera position based on the keys WASD/QE
            // S & W moves the player back and forth
            if (app->getKeyboard().isPressed(GLFW_KEY_SPACE))
            {
                MovementComponent *bulletMovement = bullet->getComponent<MovementComponent>();
                bulletMovement->linearVelocity = {0, 0, -10};
            }
            if (app->getKeyboard().isPressed(GLFW_KEY_C))
            {
                if (wait>0 && wait < interval)
                {
                    wait+= deltaTime;  // so that the keyboard press is read as one press only
                    return;
                }
                wait=0;
                MeshRendererComponent *Mesh = bullet->getComponent<MeshRendererComponent>();
                if (color == 0)
                {
                    Mesh->material = AssetLoader<Material>::get("green");
                    color = 1;
                }
                else if (color == 1)
                {
                    Mesh->material = AssetLoader<Material>::get("blue");
                    color = 2;
                }
                else if (color == 2)
                {
                    Mesh->material = AssetLoader<Material>::get("red");
                    color = 0;
                }
                wait+= deltaTime;
            }
        }
    };

}
