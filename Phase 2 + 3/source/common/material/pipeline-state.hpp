#pragma once

#include <glad/gl.h>
#include <glm/vec4.hpp>
#include <json/json.hpp>

namespace our
{
    // There are some options in the render pipeline that we cannot control via shaders
    // such as blending, depth testing and so on
    // Since each material could require different options (e.g. transparent materials usually use blending),
    // we will encapsulate all these options into a single structure that will also be responsible for configuring OpenGL's pipeline
    struct PipelineState
    {
        // This set of pipeline options specifies whether face culling will be used or not and how it will be configured
        struct
        {
            bool enabled = false;
            GLenum culledFace = GL_BACK;
            GLenum frontFace = GL_CCW;
        } faceCulling;

        // This set of pipeline options specifies whether depth testing will be used or not and how it will be configured
        struct
        {
            bool enabled = false;
            GLenum function = GL_LEQUAL;
        } depthTesting;

        // This set of pipeline options specifies whether blending will be used or not and how it will be configured
        struct
        {
            bool enabled = false;
            GLenum equation = GL_FUNC_ADD;
            GLenum sourceFactor = GL_SRC_ALPHA;
            GLenum destinationFactor = GL_ONE_MINUS_SRC_ALPHA;
            glm::vec4 constantColor = {0, 0, 0, 0};
        } blending;

        // These options specify the color and depth mask which can be used to
        // prevent the rendering/clearing from modifying certain channels of certain targets in the framebuffer
        glm::bvec4 colorMask = {true, true, true, true}; // To know how to use it, check glColorMask
        bool depthMask = true;                           // To know how to use it, check glDepthMask

        // This function should set the OpenGL options to the values specified by this structure
        // For example, if faceCulling.enabled is true, you should call glEnable(GL_CULL_FACE), otherwise, you should call glDisable(GL_CULL_FACE)
        void setup() const
        {
            if (faceCulling.enabled)
            {
                glEnable(GL_CULL_FACE);
                glCullFace(faceCulling.culledFace);
                // The face to be considered for culling - front, back, or both

                glFrontFace(faceCulling.frontFace);
                // The orientation of the front face
                // Read: https://www.khronos.org/registry/OpenGL-Refpages/es3/html/glFrontFace.xhtml
                // Order of vertices defining an object from first to last - does it go counterclockwise or clockwise - determines whether it's front-facing or not
            }
            else
                glDisable(GL_CULL_FACE);

            if (depthTesting.enabled)
            {
                glEnable(GL_DEPTH_TEST);
                glDepthFunc(depthTesting.function);
                // Depth comparison function to determine pixels to draw
                // ex. GL_LEQUAL draws the pixel if the depth value is less than or equal to the pixel's current depth value
            }
            else
                glDisable(GL_DEPTH_TEST);

            if (blending.enabled)
            {
                glEnable(GL_BLEND);
                glBlendEquation(blending.equation);
                // The equation used to combine the source and destination colors
                // ex. GL_FUNC_ADD adds the source and destination colors together (weighted with blend factors)

                glBlendFunc(blending.sourceFactor, blending.destinationFactor);
                // The source and destination blending factors
                // ex. GL_SRC_ALPHA for the source multiplies the source color with the source alpha value
                //     GL_ONE_MINUS_SRC_ALPHA for the destination multiplies the destination color with the one minus the source alpha value

                glBlendColor(blending.constantColor.r, blending.constantColor.g, blending.constantColor.b, blending.constantColor.a);
                // Setter for GL_BLEND_COLOR
                // This constant is used in some blending factors, referred to as CONSTANT (like GL_CONSTANT_COLOR and GL_CONSTANT_ALPHA)
            }
            else
                glDisable(GL_BLEND);

            glColorMask(colorMask.r, colorMask.g, colorMask.b, colorMask.a);
            // Determines which of the four channels are to be written to the framebuffer

            glDepthMask(depthMask);
            // Determines whether the depth buffer is to be written to or not
        }

        // Given a json object, this function deserializes a PipelineState structure
        void deserialize(const nlohmann::json &data);
    };

}