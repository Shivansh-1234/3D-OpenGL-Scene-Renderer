#version 330 core

#define NR_POINT_LIGHTS 1

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
uniform PointLight pointLight[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

uniform vec3 viewPos;

in vec4 vCol;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D brickTexture;

uniform sampler2D texture_diffuse1;


vec3 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight pointLight, vec3 normal , vec3 viewDir, vec3 fragPos);
vec3 calcSpotLight(SpotLight spotLight, vec3 normal , vec3 viewDir, vec3 fragPos);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = calcDirectionalLight(directionalLight, norm, viewDir);
    for(int i = 0; i < NR_POINT_LIGHTS; i++){
        result += calcPointLight(pointLight[i], norm, viewDir, FragPos);
    }
    result += calcSpotLight(spotLight, norm, viewDir, FragPos);

    FragColor =  texture(texture_diffuse1, TexCoords) * vec4(result, 1.0) * texture(brickTexture, TexCoords);
}

vec3 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 viewDir){
    // Ambient Light
    vec3 ambient = directionalLight.ambientIntensity * directionalLight.color;

    // Diffuse Light (Directional)
    vec3 lightDir = normalize(-directionalLight.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = directionalLight.diffuseIntensity * diff * directionalLight.color;

    // Specular Light (Directional)
    vec3 reflectDir = reflect(-lightDir, normal);
    float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specularIntensity * specularFactor * directionalLight.color;

    return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight pointLight, vec3 normal , vec3 viewDir, vec3 fragPos){
    // Point Light Contribution
    vec3 pointLightDir = normalize(pointLight.position - fragPos);
    float pointDiff = max(dot(normal, pointLightDir), 0.0);
    vec3 pointDiffuse = pointLight.ambientIntensity * pointDiff * pointLight.color;

    vec3 pointReflectDir = reflect(pointLightDir, normal);
    float pointSpec = pow(max(dot(viewDir, pointReflectDir), 0.0), material.shininess);
    vec3 pointSpecular = material.specularIntensity * pointSpec * pointLight.color;

    // Attenuation (Point Light)
    float distance = length(pointLight.position - fragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance +
    pointLight.quadratic * (distance * distance));
    pointDiffuse *= attenuation;
    pointSpecular *= attenuation;

    return (pointDiffuse + pointSpecular);
}

vec3 calcSpotLight(SpotLight spotLight, vec3 normal , vec3 viewDir, vec3 fragPos){
    // Spot Light Contribution
    vec3 spotLightDir = normalize(spotLight.position - fragPos);
    float theta = dot(spotLightDir, normalize(-spotLight.direction));
    float epsilon = (spotLight.cutOff - spotLight.outerCutoff);
    float intensity = clamp((theta - spotLight.outerCutoff) / epsilon, 0.0, 1.0);

    // Spot Light Diffuse and Specular
    float spotDiff = max(dot(normal, spotLightDir), 0.0);
    vec3 spotDiffuse = intensity * spotLight.ambientIntensity * spotDiff * spotLight.color;
    vec3 spotReflectDir = reflect(spotLightDir, normal);
    float spotSpec = pow(max(dot(viewDir, spotReflectDir), 0.0), material.shininess);
    vec3 spotSpecular = intensity * material.specularIntensity * spotSpec * spotLight.color;

    return (spotDiffuse + spotSpecular);
}
