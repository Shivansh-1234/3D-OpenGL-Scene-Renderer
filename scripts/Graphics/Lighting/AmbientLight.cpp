#include "AmbientLight.h"
#include "../Shader.h"

AmbientLight::AmbientLight(const glm::vec3 &color, float intensity)
    : Light(color, intensity)   {
}

void AmbientLight::useLight(const std::shared_ptr<Shader>& shader, const std::string &uniformColor,const std::string &uniformIntensity) {
    shader->setVec3(uniformColor, this->getColor());
    shader->setFloat(uniformIntensity, this->getIntensity());
}
