#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "Light.h"

class SpotLight : public Light{
public:
    SpotLight(const glm::vec3& color, float ambientIntensity,
        const glm::vec3& pos, const glm::vec3& dir, float cutOff, float outerCutoff);

    void setUniforms(const std::shared_ptr<Shader>& shader, const std::string& uniformName) const override;

    // Getters
    glm::vec3 getPosition() const;
    glm::vec3 getDirection() const;
    float getCutOff() const;
    float getOuterCutOff() const;

    // Setters
    void setPosition(const glm::vec3& pos);
    void setDirection(const glm::vec3& dir);
    void setCutOff(float cutOff);
    void setOuterCutOff(float outerCutOff);
private:
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutoff;
};

#endif //SPOTLIGHT_H
