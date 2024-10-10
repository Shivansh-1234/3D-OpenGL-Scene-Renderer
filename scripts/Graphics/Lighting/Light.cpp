#include "Light.h"
#include "../Shader.h"

Light::Light(const glm::vec3 &color, float intensity)
    : color(color), ambientIntensity(intensity) {
}

void Light::setUniforms(const std::shared_ptr<Shader>& shader, const std::string &uniformName) const {
    shader->setVec3(uniformName + ".color", color);
    shader->setFloat(uniformName + ".ambientIntensity", ambientIntensity);
}


void Light::setAmbientIntensity(float intensity) {
    this->ambientIntensity = intensity;
}
void Light::setColor(const glm::vec3& color) {
    this->color = color;
}

float Light::getAmbientIntensity() const {
    return ambientIntensity;
}
const glm::vec3& Light::getColor() const {
    return color;
}

