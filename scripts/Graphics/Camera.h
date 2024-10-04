#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CAMERA_MOVEMENT {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


class Camera {
public:
    Camera();
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    glm::mat4 getViewMatrix();
    void processKeyboardInputs(CAMERA_MOVEMENT cameraDirection, float dt);
    void processMouseInputs(float offSetX, float offSetY, GLboolean constraintPitch = true);
    void processMouseScroll(float offsetY);

    glm::vec3 position { 0.f , 0.f , 3.f };
    glm::vec3 front { 0.f , 0.f , -1.f };
    glm::vec3 up { 0.f, 1.f, 0.f };
    glm::vec3 right { 0.f, 0.f ,0.f};
    glm::vec3 worldUp { 0.f , 0.f , 0.f};

    float yaw = -90.f;
    float pitch = 0.f;
    float movementSpeed = 2.5f;
    float mouseSens = 0.3f;
    float zoom = 45.f;

    void mouse_callback(float xpos, float ypos);
    void scroll_callback(float yoffset);

private:
    void updateCameraVec();
    float lastX = 2560.f / 2.f;
    float lastY = 1440.f / 2.f;
    bool firstMove = true;
};


#endif //CAMERA_H











