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

struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 color;
    float ambientIntensity;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutoff;
    vec3 color;
    float ambientIntensity;
};

uniform DirectionalLight directionalLight;
uniform Material material;
uniform PointLight pointLight;
uniform SpotLight spotLight;

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

    // Diffuse Light (Directional)
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-directionalLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = directionalLight.diffuseIntensity * diff * directionalLight.color;

    // Specular Light (Directional)
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specularIntensity * specularFactor * directionalLight.color;

    // Spot Light Contribution
    vec3 spotLightDir = normalize(spotLight.position - FragPos);
    float theta = dot(spotLightDir, normalize(-spotLight.direction));
    float epsilon = (spotLight.cutOff - spotLight.outerCutoff);
    float intensity = clamp((theta - spotLight.outerCutoff) / epsilon, 0.0, 1.0);

    // Spot Light Diffuse and Specular
    float spotDiff = max(dot(norm, spotLightDir), 0.0);
    vec3 spotDiffuse = intensity * spotLight.ambientIntensity * spotDiff * spotLight.color;
    vec3 spotReflectDir = reflect(spotLightDir, norm);
    float spotSpec = pow(max(dot(viewDir, spotReflectDir), 0.0), material.shininess);
    vec3 spotSpecular = intensity * material.specularIntensity * spotSpec * spotLight.color;

    // Point Light Contribution
    vec3 pointLightDir = normalize(pointLight.position - FragPos);
    float pointDiff = max(dot(norm, pointLightDir), 0.0);
    vec3 pointDiffuse = pointLight.ambientIntensity * pointDiff * pointLight.color;

    vec3 pointReflectDir = reflect(-pointLightDir, norm);
    float pointSpec = pow(max(dot(viewDir, pointReflectDir), 0.0), material.shininess);
    vec3 pointSpecular = material.specularIntensity * pointSpec * pointLight.color;

    // Attenuation (Point Light)
    float distance = length(pointLight.position - FragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance +
    pointLight.quadratic * (distance * distance));
    pointDiffuse *= attenuation;
    pointSpecular *= attenuation;


    vec3 result = ambient + diffuse + specular + spotDiffuse + spotSpecular + pointDiffuse + pointSpecular;
    FragColor = texture(brickTexture, TexCoords) * vec4(result, 1.0);
}
