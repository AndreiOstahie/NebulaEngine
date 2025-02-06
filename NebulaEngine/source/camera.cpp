#include "Camera.h"

// Create camera and initialize camera values
Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch)
    : forward(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(5.0f), mouseSensitivity(0.1f), fov(45.0f) {
    position = startPosition;
    worldUp = startUp;
    yaw = startYaw;
    pitch = startPitch;
    updateCameraVectors();
}

// Returns the view matrix
glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(position, position + forward, up);
}

// Returns the projection matrix
glm::mat4 Camera::GetProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) {
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

// Update the camera's position based on a givendirection
void Camera::ProcessKeyboard(glm::vec3 direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    position += direction * velocity;
}

// Update the camera's rotation based on mouse position offset
void Camera::ProcessMouseMovement(float xOffset, float yOffset) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    // Constrain pitch
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Update the forward, right and up vectors after modifying the rotation
    updateCameraVectors();
}


void Camera::ProcessMouseScroll(float offset) {
    fov -= offset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}


// Update the camera's forward, right and up vectors
void Camera::updateCameraVectors() {
    // Re-calculate forward vector
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward = glm::normalize(newFront);

    // Re-calculate right and up vectors
    right = glm::normalize(glm::cross(forward, worldUp));
    up = glm::normalize(glm::cross(right, forward));
}
