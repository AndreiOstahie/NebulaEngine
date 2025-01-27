#pragma once
#include "libs.h"


class Camera {
public:
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float yaw;
    float pitch;

    float movementSpeed = 1.0f;
    float mouseSensitivity;
    float fov;

    Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch);

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix(float aspectRatio = 4.0f / 3.0f, float nearPlane = 0.1f, float farPlane = 100.0f);
    void ProcessKeyboard(glm::vec3 direction, float deltaTime);
    void ProcessMouseMovement(float xOffset, float yOffset);
    void ProcessMouseScroll(float yOffset);

private:
    void updateCameraVectors();
};