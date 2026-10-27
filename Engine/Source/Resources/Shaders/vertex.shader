#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;

out vec4 uColor;
out vec2 TexCoord;
out vec3 WorldNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    uColor = aColor;
    TexCoord = aTexCoord;
    WorldNormal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}