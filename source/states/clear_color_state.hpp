#pragma once

#include <application.hpp>

class ClearColorState: public our::State {
    // onInitialize() function is called once before the state starts
    void onInitialize() override {
        const auto& config = getApp()->getConfig()["scene"]["clear-color"];  
            //Read config file
        float r, g, b, a;                  
        r = config["r"];
        g = config["g"];
        b = config["b"]; 
        a = config["a"];
        glClearColor(r, g, b, a);                  
    }

    // onDraw(deltaTime) function is called every frame 
    void onDraw(double deltaTime) override {
        //At the start of frame we want to clear the screen. Otherwise we would still see the results from the previous frame.
        glClear(GL_COLOR_BUFFER_BIT);
    }
};