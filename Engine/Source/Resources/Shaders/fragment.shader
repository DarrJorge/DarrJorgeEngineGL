#version 330 core

in vec4 uColor;
out vec4 FragColor;
uniform vec3 ourColor;

void main()
{
    FragColor = uColor;
}