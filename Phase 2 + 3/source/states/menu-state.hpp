#pragma once

#include <application.hpp>

#include <asset-loader.hpp>

class MenuState : public our::State
{
    our::World world;
    our::ForwardRenderer renderer;
    our::PlayerControllerSystem playerController;

    void onInitialize() override
    {
        auto &config = getApp()->getConfig()["scene"];

        if (config.contains("assets"))
            our::deserializeAllAssets(config["assets"]);

        if (config.contains("world"))
            world.deserialize(config["world"]);
    }

    void onDraw(double deltaTime) override
    {
        playerController.update(&world, (float)deltaTime);
        for (auto &entity : world.getEntities())
        {
        }
        // auto size = getApp()->getFrameBufferSize();
        // renderer.render(&world, glm::ivec2(0, 0), size);
    }

    void onDestroy() override
    {
        playerController.exit();

        our::clearAllAssets();
    }
};