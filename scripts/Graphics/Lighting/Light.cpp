#include "Light.h"

Light::Light(const glm::vec3 &color, float intensity)
    : color(color), intensity(intensity) {
}

void Light::setIntensity(float intensity) {
    this->intensity = intensity;
}
void Light::setColor(const glm::vec3& color) {
    this->color = color;
}

float Light::getIntensity() const {
    return intensity;
}
const glm::vec3& Light::getColor() const {
    return color;
}

