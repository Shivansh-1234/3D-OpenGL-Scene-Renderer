#include "Material.h"
#include "../Shader.h"

Material::Material(const glm::vec3 &specular, float shininess)
    : specularIntensity(specular), shininess(shininess){
}

void Material::setUniforms(const std::shared_ptr<Shader>& shader, const std::string &uniformName) {
    shader->setVec3(uniformName + ".specularIntensity", specularIntensity);
    shader->setFloat(uniformName + ".shininess", shininess);
}

glm::vec3 Material::getSpecularIntensity() const {
    return specularIntensity;
}

void Material::setSpecularIntensity(const glm::vec3 &specular_intensity) {
    specularIntensity = specular_intensity;
}

float Material::getShininess() const {
    return shininess;
}

void Material::setShininess(float shininess) {
    this->shininess = shininess;
}
