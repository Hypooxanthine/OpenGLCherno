#include "Shader.h"

#include <GL/glew.h>

#include <iostream>
#include <fstream>

Shader::Shader()
{
}

Shader::~Shader()
{
    unload();
}

bool Shader::loadFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    unload();

    std::ifstream ifs;
    std::string line;

    ifs.open(vertexShaderPath);
        if (!ifs.is_open())
        {
            std::cout << "Couldn't load \"" << vertexShaderPath << "\"." << std::endl;
            return false;
        }

        std::string vertexShader;
        while (!ifs.eof())
        {
            std::getline(ifs, line);
            vertexShader += line;
            vertexShader += "\n";
        }
    ifs.close();

    ifs.open(fragmentShaderPath);
        if (!ifs.is_open())
        {
            std::cout << "Couldn't load \"" << fragmentShaderPath << "\"." << std::endl;
            return false;
        }

        std::string fragmentShader;
        while (!ifs.eof())
        {
            std::getline(ifs, line);
            fragmentShader += line;
            fragmentShader += "\n";
        }
    ifs.close();

    m_ID = CreateShader(vertexShader, fragmentShader);
    if (m_ID == 0) return false;
    
    return true;
}

void Shader::unload()
{
    if (m_ID != 0)
    {
        glDeleteProgram(m_ID);
        m_ID = 0;
    }
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compiler " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
