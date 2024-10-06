#version 330 core

struct Light {
    vec3 color;
    float intensity;
};

uniform Light ambientLight;

in vec4 vCol;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D brickTexture;

void main()
{
    vec3 ambient = ambientLight.intensity * ambientLight.color;

    vec3 result = ambient;

    FragColor = texture(brickTexture, TexCoords) * vec4(result, 1.0);
}
