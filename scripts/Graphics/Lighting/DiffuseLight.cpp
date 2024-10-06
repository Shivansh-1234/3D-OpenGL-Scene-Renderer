#include "DiffuseLight.h"
#include "../Shader.h"

DiffuseLight::DiffuseLight(const glm::vec3& color, float intensity, const glm::vec3& direction)
    : Light(color, intensity) , direction(direction){
}

void DiffuseLight::useLight(const std::shared_ptr<Shader>& shader, const std::string& uniformColor,
        const std::string& uniformIntensity, const std::string& uniformDirection){
    shader->setVec3(uniformColor, this->getColor());
    shader->setFloat(uniformIntensity, this->getIntensity());
    shader->setVec3(uniformDirection, this->getDirection());
}

glm::vec3 DiffuseLight::getDirection() const{
    return direction;
}

void DiffuseLight::SetDirection(const glm::vec3& direction){
    this->direction = direction;
}
