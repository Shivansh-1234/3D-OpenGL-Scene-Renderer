#version 330 core

struct Light {
    vec3 color;
    float intensity;
    vec3 direction;
};

struct Material {
    vec3 specular;
    float shininess;
};

uniform Light ambientLight;
uniform Light diffuseLight;
uniform Light specularLight;

uniform Material material;

uniform vec3 viewPos;

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
    vec3 lightDirDiffuse = normalize(diffuseLight.direction - FragPos);
    float diff = max(dot(norm, lightDirDiffuse), 0.0);
    vec3 diffuse = diffuseLight.intensity * diff * diffuseLight.color;

    //specular Light
    vec3 lightDirSpec = normalize(specularLight.direction - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDirSpec, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * specularLight.intensity * specularLight.color;

    vec3 result = (ambient + diffuse + specular);

    FragColor = texture(brickTexture, TexCoords) * vec4(result, 1.0);
}
