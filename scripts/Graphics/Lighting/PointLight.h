#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

class PointLight : public Light{
public:
    PointLight(const glm::vec3& color, float ambientIntensity, const glm::vec3& position, float constant,float linear,float quadratic);

    void setUniforms(const std::shared_ptr<Shader>& shader, const std::string& uniformName) const override;

    glm::vec3 setPosition() const;
    void getPosition(const glm::vec3 &position);
    float getConstant() const;
    void setConstant(float constant);
    float getLinear() const;
    void setLinear(float linear);
    float getQuadratic() const;
    void setQuadratic(float quadratic);

private:
    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;
};



#endif //POINTLIGHT_H
