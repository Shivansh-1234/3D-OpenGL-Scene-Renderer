#include "DirectionalLight.h"

#include "../Shader.h"

DirectionalLight::DirectionalLight(const glm::vec3 &color, const glm::vec3 &direction,
                                   float ambientIntensity, float diffuseIntensity)
        :Light(color, ambientIntensity),
        direction(direction),
        diffuseIntensity(diffuseIntensity)  {
}

void DirectionalLight::setUniforms(Shader &shader, const std::string &uniformName) const {
    Light::setUniforms(shader, uniformName);
    shader.setVec3(uniformName + ".direction", direction);
    shader.setFloat(uniformName + ".diffuseIntensity", diffuseIntensity);

}

void DirectionalLight::setDirection(const glm::vec3 &direction) {
    this->direction = direction;
}

void DirectionalLight::setDiffuseIntensity(float diffuse_intensity) {
    diffuseIntensity = diffuse_intensity;
}

glm::vec3 DirectionalLight::getDirection() const {
    return direction;
}

float DirectionalLight::getDiffuseIntensity() const {
    return diffuseIntensity;
}
