#pragma once

#include <string>
#include<unordered_map>
#include "vendor/glm/glm.hpp"
#include <unordered_map>

struct ShaderProgramSource{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
    
    private:
        unsigned int m_RendererID;
        std::string m_Filepath;
        std::unordered_map<std::string,int> m_uniformLocationCache;
    public:
        Shader(const std::string& filepath);
        ~Shader();
        void Bind() const;
        void Unbind() const;
        template<typename T>
        void SetUniform(const std::string& name, T value);
        
    private:
        ShaderProgramSource ParseShader(const std::string& filePath);
        unsigned int CompileShader( unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
        int GetUniformLocation(const std::string& name);
};


template<>
inline void Shader::SetUniform<float>(const std::string& name, float value)
{
    GLint location = GetUniformLocation(name);
    glUniform1f(location,value);
}
template<>
inline void Shader::SetUniform<glm::vec2>(const std::string& name, glm::vec2 value)
{
    GLint location = GetUniformLocation(name);
    glUniform2f(location,value.x,value.y);
}
template<>
inline void Shader::SetUniform<glm::vec3>(const std::string& name, glm::vec3 value)
{
    GLint location = GetUniformLocation(name);
    glUniform3f(location,value.x,value.y,value.z);
}
template<>
inline void Shader::SetUniform<glm::vec4>(const std::string& name, glm::vec4 value)
{
    GLint location = GetUniformLocation(name);
    glUniform4f(location,value.x,value.y,value.z,value.w);
}
template<>
inline void Shader::SetUniform<int>(const std::string& name, int value)
{
    GLint location = GetUniformLocation(name);
    glUniform1i(location,value);
}
template<>
inline void Shader::SetUniform<glm::mat3>(const std::string& name, glm::mat3 value)
{
    GLint location = GetUniformLocation(name);
    glUniformMatrix4fv(location,1,GL_FALSE,&value[0][0]);
}
template<>
inline void Shader::SetUniform<glm::mat4>(const std::string& name, glm::mat4 value)
{
    GLint location = GetUniformLocation(name);
    glUniformMatrix4fv(location,1,GL_FALSE,&value[0][0]);
}