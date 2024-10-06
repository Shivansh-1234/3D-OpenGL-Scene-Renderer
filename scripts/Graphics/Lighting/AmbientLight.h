#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "Light.h"
#include <iostream>
#include <memory>

class Shader;

class AmbientLight : public Light{
public:
    AmbientLight(const glm::vec3& color, float intensity);
    void useLight(const std::shared_ptr<Shader>& shader, const std::string& uniformColor, const std::string& uniformIntensity);
};



#endif //AMBIENTLIGHT_H
