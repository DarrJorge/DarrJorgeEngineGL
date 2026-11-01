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
    WorldNormal = mat3(transpose(inverse(model))) * aNormal;

    // Keep texel density constant under non-uniform scale instead of stretching: multiply UV by the
    // world-space scale of whichever two local axes are in-plane for this face. Branchless: abs(aNormal)
    // is one-hot (exactly one axis is +-1 on this flat-shaded cube); cyclic swizzles of it pick the other
    // two axes' scale in a fixed order, and the sign of the dominant axis (always exactly +-1, so step()
    // is exact) selects which of the two goes to U vs V.
    vec3 scale = vec3(length(model[0].xyz), length(model[1].xyz), length(model[2].xyz));

    vec3 absNormal = abs(aNormal);
    float scaleA = dot(absNormal.zxy, scale);
    float scaleB = dot(absNormal.yzx, scale);

    float positiveFace = step(0.0, dot(aNormal, vec3(1.0)));
    vec2 uvScale = mix(vec2(scaleB, scaleA), vec2(scaleA, scaleB), positiveFace);

    TexCoord = aTexCoord * uvScale;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}