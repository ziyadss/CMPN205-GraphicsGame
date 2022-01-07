#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <unordered_map>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace our
{
    class ShaderProgram
    {
    private:
        // Shader Program Handle
        GLuint program;

        // Uniform locations cache
        std::unordered_map<std::string, GLuint> uniformLocations;

    public:
        void create();
        void destroy();

        ShaderProgram() { program = 0; }
        ~ShaderProgram() { destroy(); }

        bool attach(const std::string &filename, GLenum type) const;

        bool link() const;

        void use()
        {
            glUseProgram(program);
        }

        GLuint getUniformLocation(const std::string &name)
        {
            // If not in cache, get location and add it
            if (uniformLocations.find(name) == uniformLocations.end())
                uniformLocations[name] = glGetUniformLocation(program, name.c_str());

            return uniformLocations[name];
        }

        void set(const std::string &uniform, GLfloat value)
        {
            glUniform1f(getUniformLocation(uniform), value);
        }

        void set(const std::string &uniform, glm::vec2 value)
        {
            glUniform2fv(getUniformLocation(uniform), 1, glm::value_ptr(value));
        }

        void set(const std::string &uniform, glm::vec3 value)
        {
            glUniform3fv(getUniformLocation(uniform), 1, glm::value_ptr(value));
        }

        void set(const std::string &uniform, glm::vec4 value)
        {
            glUniform4fv(getUniformLocation(uniform), 1, glm::value_ptr(value));
        }

        // Deleting copy constructor and assignment operator as deconstructor deletes
        //  the GL program used which would be shared between shallow copies.
        ShaderProgram(const ShaderProgram &) = delete;
        ShaderProgram &operator=(const ShaderProgram &) = delete;
    };

}

#endif