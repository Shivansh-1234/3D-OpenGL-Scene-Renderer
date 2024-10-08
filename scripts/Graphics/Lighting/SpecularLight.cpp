#include "SpecularLight.h"
#include "../Shader.h"

SpecularLight::SpecularLight(const glm::vec3& color, float intensity, const glm::vec3& direction , float shininess)
    :Light(color, intensity), direction(direction), shininess(shininess){
}

void SpecularLight::useLight(const std::shared_ptr<Shader>& shader, const std::string& uniformColor,
    const std::string& uniformIntensity, const std::string& uniformDirection,
    const std::string& uniformShininess){
    shader->setVec3(uniformColor, this->getColor());
    shader->setFloat(uniformIntensity, this->getIntensity());
    shader->setVec3(uniformDirection, this->getDirection());
    shader->setFloat(uniformShininess, this->getShininess());
}

float SpecularLight::getShininess() const{
    return shininess;
}

void SpecularLight::setShininess(float shininess){
    this->shininess = shininess;
}

glm::vec3 SpecularLight::getDirection() const{
    return direction;
}

void SpecularLight::setDirection(const glm::vec3& direction){
    this->direction = direction;
}


