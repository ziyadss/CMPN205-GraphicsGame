#pragma once

#include <application.hpp>

class ClearColorState : public our::State
{
    // onInitialize() function is called once before the state starts
    void onInitialize() override
    {
        // Get 'clear-color' object from json file
        const nlohmann::json color = getApp()->getConfig()["scene"]["clear-color"];

        // Get values for 'r', 'g', 'b' and 'a' keys from 'clear-color' object
        const float r = color.at("r"), g = color.at("g"), b = color.at("b"), a = color.at("a");

        // Clear the screen with the given color
        glClearColor(r, g, b, a);
    }

    // onDraw(deltaTime) function is called every frame
    void onDraw(double deltaTime) override
    {
        //At the start of frame we want to clear the screen. Otherwise we would still see the results from the previous frame.
        glClear(GL_COLOR_BUFFER_BIT);
    }
};