#ifndef DIFFUSELIGHT_H
#define DIFFUSELIGHT_H

#include "Light.h"
#include <memory>

class Shader;

class DiffuseLight : public Light{
public:
    DiffuseLight(const glm::vec3& color, float intensity, const glm::vec3& direction);

    void useLight(const std::shared_ptr<Shader>& shader, const std::string& uniformColor,
        const std::string& uniformIntensity, const std::string& uniformDirection);

    glm::vec3 getDirection() const;
    void SetDirection(const glm::vec3& direction);
private:
    glm::vec3 direction = glm::vec3(0.f, -1.f, 0.f);
};



#endif //DIFFUSELIGHT_H
