#pragma once
#include "level.h"
#include "mesh.h"
#include "camera.h"
#include "shader.h"

class TestLevel : public Level {
private:
    Mesh* cube = nullptr;
    Shader* defaultShader;
    Shader* phongShader;
    Shader* baseColorShader;
    Mesh suzanne, suzanne2;

    std::vector<PointLight> controllablePointLight;
    glm::vec3 controllablePointLightPosition;
    glm::vec3 controllablePointLightColor;
    float controllablePointLightSpeed = 3.5f;

    std::vector<PointLight> movingPointLights;
    std::vector<glm::mat4> movingPointLightsModelMatrices;
    float movingPointLightsRotation = 0.0f;

    Mesh pointLightMesh;
    glm::vec3 pointLightMeshScale;

public:
    void Start() override;
    void Update(float deltaTime) override;
    void HandleInput(GLFWwindow* window, float deltaTime) override;
    void HandleMouseInput(GLFWwindow* window, double xpos, double ypos) override;
};