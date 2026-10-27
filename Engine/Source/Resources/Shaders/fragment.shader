#version 330 core

in vec4 uColor;
in vec2 TexCoord;
in vec3 WorldNormal;
out vec4 FragColor;

uniform sampler2D u_texture;
uniform vec3 u_lightDirection;
uniform vec3 u_lightColor;
uniform float u_ambientStrength;

void main()
{
    vec3 normal = normalize(WorldNormal);
    float diffuseFactor = max(dot(normal, u_lightDirection), 0.0);
    vec3 light = u_ambientStrength * u_lightColor + diffuseFactor * u_lightColor;

    vec4 texColor = texture(u_texture, TexCoord);
    FragColor = vec4(light * texColor.rgb, texColor.a);
}