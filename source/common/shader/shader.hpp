#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>
namespace our {

    class ShaderProgram {

    private:
        //Shader Program Handle
        GLuint program;
        mutable std::unordered_map <std::string,GLuint> UniformLocationCache;  //a list to store uniforms locations

    public:
        void create();
        void destroy();

        ShaderProgram(){ program = 0; }
        ~ShaderProgram(){ destroy(); }

        bool attach(const std::string &filename, GLenum type) const;

        bool link() const;

        void use() { 
            //TODO: call opengl to use the program identified by this->program
            glUseProgram(program);
        }

        GLuint getUniformLocation(const std::string &name) {
            //TODO: call opengl to get the uniform location for the uniform defined by name from this->program
            //check if uniform location is already stored in cache (no need to use openGl everytime)
            if (UniformLocationCache.find(name)!=UniformLocationCache.end())
            {
                return UniformLocationCache[name];
            }
            // if location not in cache , retrieve it using opengl function and store it in cache for later use  
            GLuint location= glGetUniformLocation(program,name.c_str());
            UniformLocationCache[name]=location;
            return location;
        }

        void set(const std::string &uniform, GLfloat value) {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform1f(getUniformLocation(uniform),value);
        }

        void set(const std::string &uniform, glm::vec2 value) {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform2f(getUniformLocation(uniform),value.x,value.y);
        }

        void set(const std::string &uniform, glm::vec3 value) {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform3f(getUniformLocation(uniform),value.x,value.y,value.z);
        }

        void set(const std::string &uniform, glm::vec4 value) {
            //TODO: call opengl to set the value to the uniform defined by name
             glUniform4f(getUniformLocation(uniform),value.x,value.y,value.z,value.w);
        }


        //TODO: Delete the copy constructor and assignment operator
        ShaderProgram(ShaderProgram const &)=delete;
        ShaderProgram & operator = (ShaderProgram const &)=delete;
        //Question: Why do we do this? Hint: Look at the deconstructor
        //the underlying opengl object is destroyed in deconstructor and if object is copied and one of them 
        //destroys it it will lead to an error if the other tries to still acess it.
        //so we need to bind resource acquisition and release by the timelife of an object 
    };

}

#endif
