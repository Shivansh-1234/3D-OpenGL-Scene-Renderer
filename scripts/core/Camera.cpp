#include "Camera.h"

#include <cmath>
#include <iostream>

Camera::Camera()
    :   worldUp(up){
    updateCameraVec();
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    :   position(position), up(up), worldUp(up), yaw(yaw), pitch(pitch) {
    updateCameraVec();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position+front, up);
}

void Camera::processKeyboardInputs(CAMERA_MOVEMENT cameraDirection, float dt) {
    const float vel = movementSpeed * dt;
    switch (cameraDirection) {
        case CAMERA_MOVEMENT::LEFT:
            position -= right * vel;
            break;
        case CAMERA_MOVEMENT::RIGHT:
            position += right * vel;
            break;
        case CAMERA_MOVEMENT::FORWARD:
            position += front * vel;
            break;
        case CAMERA_MOVEMENT::BACKWARD:
            position -= front * vel;
            break;
        default:
            break;
    }
}

void Camera::processMouseInputs(float offSetX, float offSetY, GLboolean constraintPitch) {
    offSetX *= mouseSens;
    offSetY *= mouseSens;

    yaw = glm::mod( yaw + offSetX, 360.0f );

    yaw += offSetX;
    pitch += offSetY;


    if (constraintPitch) {
        if (pitch > PITCH_LIMIT)
            pitch = PITCH_LIMIT;
        if (pitch < -PITCH_LIMIT)
            pitch = -PITCH_LIMIT;
    }

    updateCameraVec();

}

void Camera::processMouseScroll(float offsetY) {
    if (zoom >= 1.f && zoom <= 45.f)
        zoom -= offsetY;
    zoom = glm::clamp(zoom, 1.f, 45.f);
}

void Camera::updateCameraVec() {
    auto tempFront = glm::vec3(1.f);
    tempFront.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    tempFront.y = std::sin(glm::radians(pitch));
    tempFront.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    front = glm::normalize(tempFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));

    //std::cout << movementSpeed << std::endl;

   // std::cout << " X : " << tempFront.x << " , Y : " << tempFront.y << " , Z : " << tempFront.z << std::endl;
}

void Camera::mouse_callback(float xpos, float ypos)  {
    if(firstMove) {
        lastX = xpos;
        lastY = ypos;
        firstMove = false;
    }

    float offSetX = xpos - lastX;
    float offSetY = lastY - ypos; //as y coord range from botton to top

    lastX = xpos;
    lastY = ypos;

    processMouseInputs(offSetX, offSetY);
}

void Camera::scroll_callback(float yoffset)  {
    processMouseScroll(yoffset);
}

