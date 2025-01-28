#pragma once
#include "level.h"
#include "mesh.h"
#include "camera.h"
#include "shader.h"

class TestLevel : public Level {
private:
    Mesh* cube = nullptr;
    Mesh* vertexColorsCube;
    Mesh suzanne, suzanne2;

    Shader* defaultShader;
    Shader* phongShader;
    Shader* baseColorShader;
    Shader* vertexColorShader;
    

    std::vector<PointLight> controllablePointLight;
    glm::vec3 controllablePointLightPosition;
    glm::vec3 controllablePointLightColor;
    float controllablePointLightSpeed = 3.5f;

    std::vector<PointLight> movingPointLights;
    std::vector<glm::mat4> movingPointLightsModelMatrices;
    float movingPointLightsRotation = 0.0f;

    Mesh pointLightMesh;
    glm::vec3 pointLightMeshScale;

    float minScale = 0.5f;
    float maxScale = 3.0f;
    float currentScale = 1.0f;
    float scalingSpeed = 1.5f;
    bool scaleUp = true;

    float currentRotation = 0.0f;
    float rotationSpeed = 50.0f;

    float minTranslation = -3.0f;
    float maxTranslation = 3.0f;
    float currentTranslation = 0.0f;
    float translationSpeed = 3.5f;
    bool translatePositive = true;
    

public:
    void Start() override;
    void Update(float deltaTime) override;
    void HandleInput(GLFWwindow* window, float deltaTime) override;
    void HandleMouseInput(GLFWwindow* window, double xpos, double ypos) override;
};