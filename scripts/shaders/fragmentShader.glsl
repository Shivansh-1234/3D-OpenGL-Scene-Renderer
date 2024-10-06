#version 330 core

struct Light {
    vec3 color;
    float intensity;
    vec3 direction;
};

uniform Light ambientLight;
uniform Light diffuseLight;

in vec4 vCol;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D brickTexture;

void main()
{
    //Ambient Light
    vec3 ambient = ambientLight.intensity * ambientLight.color;

    //Diffuse Light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(diffuseLight.direction - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseLight.intensity * diff * diffuseLight.color;

    vec3 result = ambient + diffuse;

    FragColor = texture(brickTexture, TexCoords) * vec4(result, 1.0);
}
