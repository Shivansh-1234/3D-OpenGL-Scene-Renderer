#ifndef SPECULARLIGHT_H
#define SPECULARLIGHT_H

#include "Light.h"
#include <memory>

class Shader;

class SpecularLight : public Light{
public:
    SpecularLight(const glm::vec3& color, float intensity, const glm::vec3& direction, float shininess);

    void useLight(const std::shared_ptr<Shader>& shader,
        const std::string& uniformColor,
        const std::string& uniformIntensity,
        const std::string& uniformDirection ,
        const std::string& uniformShininess
        );

    float getShininess() const;
    void setShininess(float shininess);
    glm::vec3 getDirection() const;
    void setDirection(const glm::vec3& direction);

private:
    float shininess;
    glm::vec3 direction;
};



#endif //SPECULARLIGHT_H
