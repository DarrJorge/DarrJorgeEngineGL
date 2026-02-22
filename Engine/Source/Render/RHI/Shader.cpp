#include "Shader.h"
#include "Log/Log.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogShader);


Shader::Shader(const std::string& vertexSourceCode, const std::string& fragmentSourceCode)
{
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    auto vertexShaderCode = vertexSourceCode.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        LOG(LogShader, Error, "ERROR::SHADER::VERTEX::COMPILATION_FAILED: ", infoLog);
    }

    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    auto fragShaderCode = fragmentSourceCode.c_str();
    glShaderSource(fragmentShader, 1, &fragShaderCode, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        LOG(LogShader, Error, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: ", infoLog);
    }

    // link shaders
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_shaderProgram, 512, nullptr, infoLog);
        LOG(LogShader, Error, "ERROR::SHADER::PROGRAM::LINKING_FAILED_FAILED: ", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(m_shaderProgram);
}

Shader::~Shader()
{
    glDeleteProgram(m_shaderProgram);
}