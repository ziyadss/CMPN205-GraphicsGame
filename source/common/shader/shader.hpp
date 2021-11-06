#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

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

    public:
        void create();
        void destroy();

        ShaderProgram() { program = 0; }
        ~ShaderProgram() { destroy(); }

        bool attach(const std::string &filename, GLenum type) const;

        bool link() const;

        void use()
        {
            //TODO: call opengl to use the program identified by this->program
            glUseProgram(this->program);
        }

        GLuint getUniformLocation(const std::string &name)
        {
            //TODO: call opengl to get the uniform location for the uniform defined by name from this->program
            GLuint nameLoc = glGetUniformLocation(this->program, name.c_str());
            return nameLoc;
        }

        void set(const std::string &uniform, GLfloat value)
        {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform1f(getUniformLocation(uniform), value);
        }

        void set(const std::string &uniform, glm::vec2 value)
        {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform2fv(getUniformLocation(uniform), 1, glm::value_ptr(value));
        }

        void set(const std::string &uniform, glm::vec3 value)
        {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform3fv(getUniformLocation(uniform), 1, glm::value_ptr(value));
        }

        void set(const std::string &uniform, glm::vec4 value)
        {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform4fv(getUniformLocation(uniform), 1, glm::value_ptr(value));
        }

        //TODO: Delete the copy constructor and assignment operator
        ShaderProgram(const ShaderProgram &) = delete;
        ShaderProgram &operator=(const ShaderProgram &) = delete;
        //Question: Why do we do this? Hint: Look at the deconstructor
        /*Because if we create two program pointers and assign to them the same value then ended the program by deleting one of them, 
        The other one will still point to the same place in memory and can be used to access data that is no longer there.
        We solve this problem by deleting the copy constructor and assignment operator and therefore not allowing this situation to happen*/
    };

}

#endif