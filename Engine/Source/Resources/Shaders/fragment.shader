#version 330 core


out vec4 FragColor;

uniform vec3 lightColor;

float near = 0.1;
float far = 10.0;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return = (2.0 * near * far) / (far + near - z *(far - near));
}

void main()
{
    //FragColor = uColor;
    //FragColor = texture(Texture, TexCoord);

    //float depth = LinearizeDepth(gl_FragCoord.z) / far;
    //FragColor = vec4(vec3(depth), 1.0);

    FragColor = vec4(lightColor, 1.0);
}