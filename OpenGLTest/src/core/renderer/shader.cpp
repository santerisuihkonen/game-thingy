#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace Core
{
    Shader::Shader(const std::string& filepath)
        : _filepath(filepath), _rendererId(0)
    {
        ShaderProgramSource source = this->parseShader(filepath);
        this->_rendererId = this->createShader(source.VertexSource, source.FragmentSource);
    }

    Shader::~Shader()
    {
        glDeleteProgram(this->_rendererId);
    }

    void Shader::set() const
    {
        glUseProgram(this->_rendererId);
    }

    void Shader::unset() const
    {
        glUseProgram(0);
    }

    ShaderProgramSource Shader::parseShader(const std::string& filepath) {
        std::ifstream stream(filepath);

        enum class ShaderType {
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1,
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;

        while (getline(stream, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos) {
                    type = ShaderType::FRAGMENT;
                }
                else {
                    std::cout << "ERRORI" << std::endl;
                }
            }
            else {
                ss[(int)type] << line << '\n';
            }
        }

        return { ss[0].str(), ss[1].str() };
    }

    unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << "Shader compilation failure!" << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
        unsigned int program = glCreateProgram();
        unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    void Shader::setUniform1i(const std::string& name, int value)
    {
        glUniform1i(this->getUniformLocation(name), value);
    }

    void Shader::setUniform1f(const std::string& name, float value)
    {
        glUniform1f(this->getUniformLocation(name), value);
    }

    void Shader::setUniformVec3(const std::string& name, float f0, float f1, float f2)
    {
        glUniform3f(this->getUniformLocation(name), f0, f1, f2);
    }

    void Shader::setUniformVec3(const std::string& name, glm::vec3 v)
    {
        glUniform3fv(this->getUniformLocation(name), 1, glm::value_ptr(v));
    }

    void Shader::setUniformVec4(const std::string& name, float f0, float f1, float f2, float f3)
    {
        glUniform4f(this->getUniformLocation(name), f0, f1, f2, f3);
    }

    void Shader::setUniformMat4(const std::string& name, glm::mat4 value)
    {
        glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    int Shader::getUniformLocation(const std::string& name)
    {
        if (this->_uniformLocationCache.find(name) != this->_uniformLocationCache.end()) {
            return this->_uniformLocationCache[name];
        }

        int location = glGetUniformLocation(this->_rendererId, name.c_str());

        if (location == -1) {
            std::cout << "Uniform '" << name << "' doesn't exist." << std::endl;
        }
        else {
            this->_uniformLocationCache[name] = location;
        }

        return location;
    }
}
