#include "PointLight.h"

#include "../Shader.h"

PointLight::PointLight(const glm::vec3& color,const float ambientIntensity, const glm::vec3& position, const float constant, const float linear, const float quadratic)
    :   Light(color, ambientIntensity),
        position(position),
        constant(constant),
        linear(linear),
        quadratic(quadratic) {
}

void PointLight::setUniforms(const std::shared_ptr<Shader> &shader, const std::string &uniformName) const {
    Light::setUniforms(shader, uniformName);
    shader->setVec3(uniformName + ".position", this->position);
    shader->setFloat(uniformName + ".constant", this->constant);
    shader->setFloat(uniformName + ".linear", this->linear);
    shader->setFloat(uniformName + ".quadratic", this->quadratic);
}

glm::vec3 PointLight::setPosition() const {
    return position;
}

void PointLight::getPosition(const glm::vec3 &position) {
    this->position = position;
}

float PointLight::getConstant() const {
    return constant;
}

void PointLight::setConstant(float constant) {
    this->constant = constant;
}

float PointLight::getLinear() const {
    return linear;
}

void PointLight::setLinear(float linear) {
    this->linear = linear;
}

float PointLight::getQuadratic() const {
    return quadratic;
}

void PointLight::setQuadratic(float quadratic) {
    this->quadratic = quadratic;
}


