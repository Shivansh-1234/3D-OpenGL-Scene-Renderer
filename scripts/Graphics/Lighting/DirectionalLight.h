#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight : public Light{
public:
    DirectionalLight(const glm::vec3& color, const glm::vec3& direction,
        float ambientIntensity, float diffuseIntensity);

    void setUniforms(const std::shared_ptr<Shader>& shader, const std::string &uniformName) const override;

    // g n s
    void setDirection(const glm::vec3 &direction);
    void setDiffuseIntensity(float diffuse_intensity);
    glm::vec3 getDirection() const;
    float getDiffuseIntensity() const;
private:
    glm::vec3 direction;
    float diffuseIntensity;
};



#endif //DIRECTIONALLIGHT_H
