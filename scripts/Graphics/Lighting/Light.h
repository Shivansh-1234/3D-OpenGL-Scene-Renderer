#ifndef LIGHT_H
#define LIGHT_H

#include <string>
#include <glm/glm.hpp>
#include <memory>

class Shader;

class Light {
public:
    virtual ~Light() = default;

    Light(const glm::vec3& color, float intensity);

    virtual void setUniforms(const std::shared_ptr<Shader>& shader, const std::string& uniformName) const;

    void setAmbientIntensity(float intensity);
    void setColor(const glm::vec3 &color);

    float getAmbientIntensity() const;
    const glm::vec3& getColor() const;

protected:
    float ambientIntensity = 1.f;
    glm::vec3 color = glm::vec3(1.f);
};


#endif //LIGHT_H
