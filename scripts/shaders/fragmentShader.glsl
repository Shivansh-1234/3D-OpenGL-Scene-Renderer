#version 330 core

struct DirectionalLight {
    vec3 color;
    vec3 direction;
    float ambientIntensity;
    float diffuseIntensity;
};

struct Material {
    vec3 specularIntensity;
    float shininess;
};

uniform DirectionalLight directionalLight;
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
    // Ambient Light
    vec3 ambient = directionalLight.ambientIntensity * directionalLight.color;

    // Diffuse Light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(directionalLight.direction - FragPos);  // Light direction is opposite to the direction of light source
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = directionalLight.diffuseIntensity * diff * directionalLight.color;

    // Specular Light
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specularIntensity * specularFactor * directionalLight.color;

    // Final result combining ambient, diffuse, and specular lighting
    vec3 result = (ambient + diffuse + specular) * texture(brickTexture, TexCoords).rgb;

    // Apply the texture and output the final fragment color
    FragColor = vec4(result, 1.0);
}