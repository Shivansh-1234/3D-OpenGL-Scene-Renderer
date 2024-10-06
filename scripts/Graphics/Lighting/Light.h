#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light {
public:
    Light(const glm::vec3& color, float intensity);

    void setIntensity(float intensity);
    void setColor(const glm::vec3 &color);

    float getIntensity() const;
    const glm::vec3& getColor() const;

protected:
    float intensity = 1.f;
    glm::vec3 color = glm::vec3(1.f);
};


#endif //LIGHT_H
