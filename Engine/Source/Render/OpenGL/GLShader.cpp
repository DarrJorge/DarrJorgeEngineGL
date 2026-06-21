#include "GLShader.h"
#include "Log/Log.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogShader);

GLShader::GLShader(const std::string& vertexSourceCode, const std::string& fragmentSourceCode)
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

GLShader::~GLShader()
{
    glDeleteProgram(m_shaderProgram);
}

void GLShader::bind() const
{
    glUseProgram(m_shaderProgram);
}

void GLShader::unbind() const
{
    glUseProgram(0);
}

GLint GLShader::getUniformLocation(std::string_view name)
{
    auto it = m_uniformCache.find(std::string(name));

    if (it != m_uniformCache.end())
    {
        return it->second;
    }

    GLint location = glGetUniformLocation(m_shaderProgram, name.data());

    m_uniformCache.emplace(std::string(name), location);

    return location;
}

void GLShader::setInt(std::string_view name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void GLShader::setFloat(std::string_view name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

void GLShader::setVec3(std::string_view name, float x, float y, float z)
{
    glUniform3f(getUniformLocation(name), x, y, z);
}

void GLShader::setVec4(std::string_view name, float x, float y, float z, float w)
{
    glUniform4f(getUniformLocation(name), x, y, z, w);
}

void GLShader::setMat4(std::string_view name, const float* matrix)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix);
}