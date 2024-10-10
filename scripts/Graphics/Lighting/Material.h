#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <glm/glm.hpp>
#include <memory>

#include "../Shader.h"

class Shader;

class Material {
public:
    Material(const glm::vec3& specular, float shininess);

    void setUniforms(const std::shared_ptr<Shader>& shader, const std::string& uniformName);

    glm::vec3 getSpecularIntensity() const;
    void setSpecularIntensity(const glm::vec3 &specular_intensity);
    float getShininess() const;
    void setShininess(float shininess);

private:
    glm::vec3 specularIntensity;
    float shininess;
};



#endif //MATERIAL_H
