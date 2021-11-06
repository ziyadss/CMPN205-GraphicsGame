#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace our {

    class ShaderProgram {

    private:
        //Shader Program Handle
        GLuint program;

    public:
        void create();
        void destroy();

        ShaderProgram(){ program = 0; }
        ~ShaderProgram(){ destroy(); }

        bool attach(const std::string &filename, GLenum type) const;

        bool link() const;

        void use() { 
            glUseProgram(this->program);
        }

        GLuint getUniformLocation(const std::string &name) {
            return glGetUniformLocation(this->program, &name[0]); //use the contiguous memory allocation property     
            //must check where used that the return is not -1
        }
            

        void set(const std::string &uniform, GLfloat value) {
            glUniform1f(getUniformLocation(uniform), value);
            
        }

        void set(const std::string &uniform, glm::vec2 value) {
            glUniform2f(getUniformLocation(uniform), value.x, value.y);
        }

        void set(const std::string &uniform, glm::vec3 value) {
            glUniform3f(getUniformLocation(uniform), value.x, value.y, value.z);
        }

        void set(const std::string &uniform, glm::vec4 value) {
            glUniform4f(getUniformLocation(uniform), value.x, value.y, value.z, value.w);
        }


        //TODO: Delete the copy constructor and assignment operator
        ShaderProgram(const ShaderProgram&) = delete; 
        ShaderProgram& operator = (const ShaderProgram&) = delete;
        //Question: Why do we do this? Hint: Look at the deconstructor
    };

}

#endif