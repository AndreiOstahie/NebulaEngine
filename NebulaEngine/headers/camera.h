#pragma once
#include "libs.h"


class Camera {
public:
    // Camera parameters
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

    // Constructor
    Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch);

    // Calculate the view and projection matrices.
    // These matrices are passed to shaders to render objects in the scene according to the camera.
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix(float aspectRatio = 4.0f / 3.0f, float nearPlane = 0.1f, float farPlane = 100.0f);

    // Functions used to re-calculate the camera's parameters (position, rotation etc.) based on user input.
    // These are used in the Level base class when processing user input.
    void ProcessKeyboard(glm::vec3 direction, float deltaTime);
    void ProcessMouseMovement(float xOffset, float yOffset);
    void ProcessMouseScroll(float offset);

private:
    // Used to re-calculate the camera's vectors after changing the camera's rotation (pitch and yaw)
    void updateCameraVectors();
};