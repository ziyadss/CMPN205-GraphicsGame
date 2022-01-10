#pragma once
#include "../ecs/world.hpp"
#include "../components/free-player-controller.hpp"

#include "../components/movement.hpp"
#include "../components/mesh-renderer.hpp"

#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

const int COLORS_COUNT = 6;
const glm::vec4 COLORS[COLORS_COUNT] = {
    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), // red
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), // green
    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), // blue
    glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), // yellow
    glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), // magenta
    glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), // cyan
};

namespace our
{

    // The free player controller system is responsible for moving every entity which contains a FreePlayerControllerComponent.
    // This system is added as a slightly complex example for how use the ECS framework to implement logic.
    // For more information, see "common/components/free-player-controller.hpp"
    class FreePlayerControllerSystem
    {
        Application *app;      // The application in which the state runs
        float wait = 0.0f;     // time to wait for keypresses
        float interval = 0.5f; // time taken before reading another key

        int color = 0;

    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
        }

        // This should be called every frame to update all entities containing a FreePlayerControllerComponent
        void update(World *world, float deltaTime)
        {
            FreePlayerControllerComponent *controller = nullptr;
            Entity *bullet = nullptr;
            if (wait > 0)
                wait += deltaTime;

            // First of all, we search for an entity containing both a PlayerComponent and a FreePlayerControllerComponent
            // As soon as we find one, we break

            for (auto entity : world->getEntities())
            {
                controller = entity->getComponent<FreePlayerControllerComponent>();
                if (entity->name == "bullet")
                    bullet = entity;
                if (controller && bullet)
                    break;
            }
            // If there is no entity with both a PlayerComponent and a FreePlayerControllerComponent, we can do nothing so we return
            if (!controller || !bullet)
                return;
            // Get the entity that we found via getOwner of player (we could use controller->getOwner())
            Entity *player = controller->getOwner();

            // We change the player position based on the keys WASD/QE
            // S & W moves the player back and forth
            if (app->getKeyboard().isPressed(GLFW_KEY_SPACE))
            {
                MovementComponent *bulletMovement = bullet->getComponent<MovementComponent>();
                bulletMovement->linearVelocity = {0, 0, -10};
            }

            if (app->getKeyboard().isPressed(GLFW_KEY_C))
            {
                if (wait > 0 && wait < interval)
                {
                    wait += deltaTime; // so that the keyboard press is read as one press only
                    return;
                }

                auto bullet_color = &dynamic_cast<TintedMaterial *>(bullet->getComponent<MeshRendererComponent>()->material)->tint;
                *bullet_color = {0, 0, 0, 0};

                color = (color + 1) % COLORS_COUNT;
                *bullet_color = COLORS[color];

                wait = deltaTime;
            }
        }
    };

}
