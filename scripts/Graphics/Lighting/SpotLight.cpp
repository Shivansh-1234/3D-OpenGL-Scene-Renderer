#include "SpotLight.h"
#include "../Shader.h"

SpotLight::SpotLight(const glm::vec3& color, float ambientIntensity, const glm::vec3& pos, const glm::vec3& dir, const float cutOff, const float outerCutoff)
    :   Light(color, ambientIntensity),
        position(pos),
        direction(dir),
        cutOff(cutOff),
        outerCutoff(outerCutoff) {

}

void SpotLight::setUniforms(const std::shared_ptr<Shader>& shader, const std::string& uniformName) const {
    Light::setUniforms(shader, uniformName);
    shader->setVec3(uniformName  + ".position", position);
    shader->setVec3(uniformName  + ".direction", direction);
    shader->setFloat(uniformName + ".cutOff", cutOff);
    shader->setFloat(uniformName + ".outerCutoff", outerCutoff);
}

// Getters
glm::vec3 SpotLight::getPosition() const {
    return position;
}

glm::vec3 SpotLight::getDirection() const {
    return direction;
}

float SpotLight::getCutOff() const {
    return cutOff;
}

float SpotLight::getOuterCutOff() const {
    return outerCutoff;
}


// Setters
void SpotLight::setPosition(const glm::vec3& pos) {
    position = pos;
}

void SpotLight::setDirection(const glm::vec3& dir) {
    direction = dir;
}

void SpotLight::setCutOff(float cutOff) {
    this->cutOff = cutOff;
}

void SpotLight::setOuterCutOff(float outerCutOff) {
    this->outerCutoff = outerCutoff;
}


